// basl_LRBTParser.cpp
//

#include "basl_LRBTParser.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_LRBTParser.inl"
#endif
// std lib
#include <algorithm>
#include <cassert>
#include <iostream>

// basil
#include "basl_ErrorRec.h"
#include "basl_Lexer.h"
#include "basl_Message.h"
#include "basl_Node.h"
#include "basl_NodePool.h"
#include "basl_Parser.h"
#include "basl_RecCmd.h"
#include "basl_RefStack.tpl"

// util
#include "util_IdentToString.h"
#define LZZ_INLINE inline
namespace
{
  using namespace basl;
}
namespace
{
  using namespace std;
}
namespace
{
  LRActionSeq lookupActionSeq (LRMove const * move_sel, int token_number);
}
namespace
{
  int lookupGotoState (LRGoto const * goto_sel, int index);
}
namespace
{
  struct PendingLRParser
  {
    LRParser lr_parser;
    LRActionSeq action_seq;
    PendingLRParser (LRParser const & lr_parser, LRActionSeq action_seq);
  };
}
namespace
{
  typedef std::deque <PendingLRParser> PendingLRParserDeque;
}
namespace
{
  typedef std::deque <PendingLRParser>::iterator PendingLRParserDequeIter;
}
namespace
{
  struct InsertToken
  {
    TokenList & token_set;
    TokenListIter & p;
    util::Loc const & loc;
    void operator () (FreeToken const & free_token) const;
  public:
    explicit InsertToken (TokenList & token_set, TokenListIter & p, util::Loc const & loc);
    ~ InsertToken ();
  };
}
namespace
{
  TokenListIter insertTokens (TokenList & token_set, TokenListIter p, util::Loc const & loc, FreeTokenVector const & free_token_set);
}
namespace
{
  TokenListIter moveTokens (TokenList & token_set, TokenListIter p, TokenListIter q, TokenListIter t);
}
namespace
{
  struct CanRecover
  {
    LRBTParser & lrbt_parser;
    LRParser const & start_lr_parser;
    LRParser & lr_parser;
    bool operator () (RecCmdPtr const & rec_cmd) const;
  public:
    explicit CanRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser);
    ~ CanRecover ();
  };
}
namespace basl
{
  using namespace std;
}
namespace basl
{
  template class RefStack <SG>;
}
namespace
{
  LRActionSeq lookupActionSeq (LRMove const * move_sel, int token_number)
  {
    // first element contains size and default action sequence
    int num = move_sel->token_number;
    LRActionSeq action_seq = move_sel->action_seq;
    // perform binary search
    if (num != 0)
    {
      LRMove const * beg = move_sel + 1;
      LRMove const * end = beg + num;
      for (;;)
      {
        int n = end - beg;
        if (n == 1)
        {
          break;
        }
        LRMove const * p = beg + (n >> 1);
        if (token_number < p->token_number)
        {
          end = p;
        }
        else
        {
          beg = p;
        }
      }
      if (token_number == beg->token_number)
      {
        action_seq = beg->action_seq;
      }
    }
    return action_seq;
  }
}
namespace
{
  int lookupGotoState (LRGoto const * goto_sel, int index)
  {
    // first element contains size and default state
    int state = goto_sel->state;
    int num = goto_sel->index;
    // perform binary search
    if (num != 0)
    {
      LRGoto const * beg = goto_sel + 1;
      LRGoto const * end = beg + num;
      for (;;)
      {
        int n = end - beg;
        if (n == 1)
        {
          break;
        }
        LRGoto const * p = beg + (n >> 1);
        if (index < p->index)
        {
          end = p;
        }
        else
        {
          beg = p;
        }
      }
      if (index == beg->index)
      {
        state = beg->state;
      }
    }
    return state;
  }
}
namespace
{
  LZZ_INLINE PendingLRParser::PendingLRParser (LRParser const & lr_parser, LRActionSeq action_seq)
    : lr_parser (lr_parser), action_seq (action_seq)
    {}
}
namespace
{
  LZZ_INLINE void InsertToken::operator () (FreeToken const & free_token) const
  {
    p = token_set.insert (p, Token (free_token.number, loc, free_token.lexeme));
  }
}
namespace
{
  LZZ_INLINE InsertToken::InsertToken (TokenList & token_set, TokenListIter & p, util::Loc const & loc)
    : token_set (token_set), p (p), loc (loc)
              {}
}
namespace
{
  InsertToken::~ InsertToken ()
              {}
}
namespace
{
  TokenListIter insertTokens (TokenList & token_set, TokenListIter p, util::Loc const & loc, FreeTokenVector const & free_token_set)
  {
    std::for_each (free_token_set.rbegin (), free_token_set.rend (), InsertToken (token_set, p, loc));
    return p;
  }
}
namespace
{
  TokenListIter moveTokens (TokenList & token_set, TokenListIter p, TokenListIter q, TokenListIter t)
  {
    for (; q != p;)
    {
      -- q;
      t = token_set.insert (t, Token (q->getNumber (), t->getLoc (), q->getLexeme ()));
    }
    return t;
  }
}
namespace
{
  bool CanRecover::operator () (RecCmdPtr const & rec_cmd) const
  {
    return rec_cmd->canRecover (lrbt_parser, start_lr_parser, lr_parser);
  }
}
namespace
{
  LZZ_INLINE CanRecover::CanRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser)
    : lrbt_parser (lrbt_parser), start_lr_parser (start_lr_parser), lr_parser (lr_parser)
       {}
}
namespace
{
  CanRecover::~ CanRecover ()
       {}
}
namespace basl
{
  int LRBTParser::getLexState (LRParser const & lr_parser) const
    {
      LRState const & state = data.state_set [lr_parser.sg_stack.back ().state_num];
      return state.lex_state;
    }
}
namespace basl
{
  TokenListIter LRBTParser::getNextToken (TokenListIter token_iter, int lex_state)
    {
      if (++ token_iter == token_set.end ())
      {
        token_iter = token_set.insert (token_iter, lexer.getNextToken (lex_state));
      }
      return token_iter;
    }
}
namespace basl
{
  LRActionSeq LRBTParser::getActionSeq (LRParser const & lr_parser) const
    {
      int token_number = (* lr_parser.token_iter).getNumber ();
      LRMove const * move_sel = data.state_set [lr_parser.sg_stack.back ().state_num].move_sel;
      return lookupActionSeq (move_sel, token_number);
    }
}
namespace basl
{
  void LRBTParser::shift (LRParser & lr_parser, LRAction action, bool guess, bool backtrack)
    {
      Token const & token = * lr_parser.token_iter;
      Node * node = lr_parser.tree.pointer ();
      lr_parser.tree = getNode (node, token, 0, node);
      int s1 = lr_parser.sg_stack.back ().state_num;
      int s2 = action [1];
      int guess_cnt = guess ? 1 : 0;
      lr_parser.sg_stack.push_back (SG (s2, guess_cnt));
      if (trace)
      {
        std::cout.width (4);
        std::cout << s1;
        std::cout.width (5);
        std::cout << s2;
        std::cout << ' ' << (guess ? '?' : ' ') << (backtrack ? '<' : ' ') << "       " << identToString (token.getLexeme ()) << std::endl;
      }
      setNextToken (lr_parser);
    }
}
namespace basl
{
  bool LRBTParser::reduce (LRParser & lr_parser, LRAction action, bool guess, bool backtrack, int & num_cancel)
    {
      LRRule const & rule = data.rule_set [action [1]];
      if (! (rule.size == 1 && rule.nonterm_info == 0))
      {
        Node * node = lr_parser.tree.pointer ();
        Node * prev = node->getPrev (rule.size);
        if (rule.nonterm_info != 0)
        {
          lr_parser.tree = getNode (prev, Token (), & rule, node);
          if (! parser.onNode (lr_parser.tree.getNode ().getNonterm ()))
          {
            return false;
          }
        }
        else
        {
          lr_parser.tree = getNode (prev, Token (), 0, prev);
        }
      }
      int s1 = lr_parser.sg_stack.back ().state_num;
      if (action [0] != LR_DONE)
      {
        int guess_cnt = guess ? 1 : 0;
        for (int i = rule.size; i > 0; -- i)
        {
          guess_cnt += lr_parser.sg_stack.back ().guess_cnt;
          lr_parser.sg_stack.pop_back ();
        }
        LRState const & state = data.state_set [lr_parser.sg_stack.back ().state_num];
        LRGoto const * goto_sel = data.symbol_set [action [2]].goto_sel;
        int s2 = lookupGotoState (goto_sel, state.goto_index);
        if (action [0] == LR_ACCEPT)
        {
          num_cancel = guess_cnt;
          lr_parser.guess_cnt -= num_cancel;
          guess_cnt = 0;
        }
        lr_parser.sg_stack.push_back (SG (s2, guess_cnt));
        if (trace)
        {
          cout.width (4);
          cout << s1;
          cout.width (5);
          cout << s2;
          if (action [0] == LR_ACCEPT)
          {
            cout << ' ' << (guess ? '?' : ' ') << (backtrack ? '<' : ' ') << (lr_parser.guess_cnt == 0 ? '!' : '*');
            cout.width (5);
            cout << num_cancel;
          }
          else
          {
            cout << ' ' << (guess ? '?' : ' ') << (backtrack ? '<' : ' ') << "      ";
          }
          cout << ' ' << rule.str << '\n';
        }
      }
      else
      {
        done = true;
        if (trace)
        {
          cout.width (4);
          cout << s1;
          cout << "               " << rule.str << '\n';
        }
      }
      return true;
    }
}
namespace basl
{
  bool LRBTParser::dfParse (LRParser & lr_parser)
    {
      bool result = false;
      LRActionSeq action_seq;
      bool lookup = true;
      PendingLRParserDeque pending_lr_parser_set;
      for (;;)
      {
        bool backtrack = ! lookup;
        if (lookup)
        {
          lookup = false;
          action_seq = getActionSeq (lr_parser);
        }
        else
        {
          // syntax error if pending parser set is empty
          if (pending_lr_parser_set.empty ())
          {
            result = false;
            break;
          }
          PendingLRParser const & pending_lr_parser = pending_lr_parser_set.front ();
          lr_parser = pending_lr_parser.lr_parser;
          action_seq = pending_lr_parser.action_seq;
          pending_lr_parser_set.pop_front ();
        }
        LRAction action = * action_seq ++;
        if (action)
        {
          // guess if remaining actions
          bool guess = false;
          if (* action_seq)
          {
            guess = true;
            pending_lr_parser_set.push_front (PendingLRParser (lr_parser, action_seq));
            ++ lr_parser.guess_cnt;
          }
          // do action
          if (* action == LR_SHIFT)
          {
            shift (lr_parser, action, guess, backtrack);
            lookup = true;
          }
          else
          {
            int num_cancel;
            if (reduce (lr_parser, action, guess, backtrack, num_cancel))
            {
              lookup = true;
              if (* action == LR_DONE)
              {
                result = true;
                break;
              }
              else if (* action == LR_ACCEPT)
              {
                // cancel pending parsers, full accept if guess count goes to zero
                if (lr_parser.guess_cnt == 0)
                {
                  result = true;
                  break;
                }
                // cancel pending lr parsers
                if (num_cancel >= pending_lr_parser_set.size ())
                {
                  pending_lr_parser_set.clear ();
                }
                else
                {
                  pending_lr_parser_set.erase (pending_lr_parser_set.begin (), pending_lr_parser_set.begin () + num_cancel);
                }
              }
            }
          }
        }
      }
      return result;
    }
}
namespace basl
{
  void LRBTParser::bfParse (LRParser & lr_parser, LRParserDeque & lr_parser_set)
    {
      LRActionSeq action_seq;
      bool lookup = true;
      PendingLRParserDeque pending_lr_parser_set;
      for (;;)
      {
        // either lookup next action seq or backtrack
        if (lookup)
        {
          lookup = false;
          action_seq = getActionSeq (lr_parser);
        }
        else
        {
          // finished if pending parser set is empty
          if (pending_lr_parser_set.empty ())
          {
            break;
          }
          PendingLRParser const & pending_parser = pending_lr_parser_set.front ();
          lr_parser = pending_parser.lr_parser;
          action_seq = pending_parser.action_seq;
          pending_lr_parser_set.pop_front ();
        }
        LRAction action = * action_seq ++;
        if (action)
        {
          // guess if remaining actions
          bool guess = false;
          if (* action_seq)
          {
            guess = true;
            pending_lr_parser_set.push_front (PendingLRParser (lr_parser, action_seq));
            ++ lr_parser.guess_cnt;
          }
          // do action
          if (* action == LR_SHIFT)
          {
            shift (lr_parser, action, guess, false);
            lr_parser_set.push_back (lr_parser);
          }
          else
          {
            int num_cancel;
            if (reduce (lr_parser, action, guess, false, num_cancel))
            {
              lookup = true;
              if (* action == LR_DONE)
              {
                lookup = false;
              }
              else if (* action == LR_ACCEPT)
              {
                if (lr_parser.guess_cnt == 0)
                {
                  lookup = false;
                }
                else
                {
                  // cancel pending lr parsers
                  if (num_cancel >= pending_lr_parser_set.size ())
                  {
                    pending_lr_parser_set.clear ();
                  }
                  else
                  {
                    pending_lr_parser_set.erase (pending_lr_parser_set.begin (), pending_lr_parser_set.begin () + num_cancel);
                  }
                }
              }
            }
          }
        }
      }
    }
}
namespace basl
{
  bool LRBTParser::insertSome (LRParser const & start_lr_parser, FreeTokenVector const & free_token_set, LRParser & lr_parser)
    {
      LRParserDeque lr_parser_set;
      lr_parser_set.push_back (start_lr_parser);
      while (! lr_parser_set.empty ())
      {
        LRParser const & first_lr_parser = lr_parser_set.front ();
        TokenListIter p = first_lr_parser.token_iter;
        // if inserting same token then don't even try it (when inserting one token only)
        if (free_token_set.size () > 1 || free_token_set.front ().number != p->getNumber ())
        {
          TokenListIter q = insertTokens (token_set, p, p->getLoc (), free_token_set);
          for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
          {
            lr_parser = * i;
            lr_parser.token_iter = q;
            if (dfParse (lr_parser))
            {
              msg::insertingTokens (p->getLoc (), p->getLexeme (), free_token_set);
              return true;
            }
          }
          // failed, so erase it
          token_set.erase (q, p);
        }
        // step all parsers one token only
        LRParserDeque next_lr_parser_set;
        for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
        {
          lr_parser = * i;
          bfParse (lr_parser, next_lr_parser_set);
        }
        lr_parser_set.swap (next_lr_parser_set);
      }
      return false;
    }
}
namespace basl
{
  bool LRBTParser::discardSome (LRParser const & start_lr_parser, int max_discard, LRParser & lr_parser)
    {
      for (int num_discard = 1; num_discard <= max_discard; ++ num_discard)
      {
        LRParserDeque lr_parser_set;
        lr_parser_set.push_back (start_lr_parser);
        while (! lr_parser_set.empty ())
        {
          LRParser const & first_lr_parser = lr_parser_set.front ();
          TokenListIter p = first_lr_parser.token_iter;
          TokenListIter q = p;
          int cnt = 0;
          for (; cnt < num_discard && q->getNumber () != 0; ++ cnt)
          {
            q = getNextToken (q, getLexState (first_lr_parser));
          }
          if (cnt != num_discard)
          {
            break;
          }
          for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
          {
            lr_parser = * i;
            lr_parser.token_iter = q;
            if (dfParse (lr_parser))
            {
              msg::discardingTokens (p->getLoc (), p->getLexeme (), num_discard);
              return true;
            }
          }
          LRParserDeque next_lr_parser_set;
          for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
          {
            lr_parser = * i;
            bfParse (lr_parser, next_lr_parser_set);
          }
          lr_parser_set.swap (next_lr_parser_set);
        }
      }
      return false;
    }
}
namespace basl
{
  bool LRBTParser::discardOne (LRParser const & start_lr_parser, int number, LRParser & lr_parser)
    {
      LRParserDeque lr_parser_set;
      lr_parser_set.push_back (start_lr_parser);
      while (! lr_parser_set.empty ())
      {
        // discard token if number matches
        LRParser const & first_lr_parser = lr_parser_set.front ();
        TokenListIter p = first_lr_parser.token_iter;
        if (p->getNumber () == number && number != 0)
        {
          TokenListIter q = getNextToken (p, getLexState (first_lr_parser));
          for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
          {
            lr_parser = * i;
            lr_parser.token_iter = q;
            if (dfParse (lr_parser))
            {
              msg::discardingTokens (p->getLoc (), p->getLexeme (), 1);
              return true;
            }
          }
        }
        // parse next tokne
        LRParserDeque next_lr_parser_set;
        for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
        {
          lr_parser = * i;
          bfParse (lr_parser, next_lr_parser_set);
        }
        lr_parser_set.swap (next_lr_parser_set);
      }
      return false;
    }
}
namespace basl
{
  bool LRBTParser::replaceSome (LRParser const & start_lr_parser, int max_discard, FreeTokenVector const & free_token_set, LRParser & lr_parser)
    {
      for (int num_discard = 1; num_discard <= max_discard; ++ num_discard)
      {
        LRParserDeque lr_parser_set;
        lr_parser_set.push_back (start_lr_parser);
        while (! lr_parser_set.empty ())
        {
          // discard num_discard tokens
          LRParser const & first_lr_parser = lr_parser_set.front ();
          TokenListIter p = first_lr_parser.token_iter;
          TokenListIter q = p;
          int cnt = 0;
          // don't discard EOT (symbol 0)
          for (; cnt < num_discard && q->getNumber () != 0; ++ cnt)
          {
            q = getNextToken (q, getLexState (first_lr_parser));
          }
          if (cnt != num_discard)
          {
            break;
          }
          // insert free_token_set
          TokenListIter r = insertTokens (token_set, q, p->getLoc (), free_token_set);
          for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
          {
            lr_parser = * i;
            lr_parser.token_iter = r;
            if (dfParse (lr_parser))
            {
              msg::replacingTokens (p->getLoc (), p->getLexeme (), num_discard, free_token_set);
              return true;
            }
          }
          // failed, so erase it
          token_set.erase (r, q);
          // step all parsers one token only
          LRParserDeque next_lr_parser_set;
          for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
          {
            lr_parser = * i;
            bfParse (lr_parser, next_lr_parser_set);
          }
          lr_parser_set.swap (next_lr_parser_set);
        }
      }
      return false;
    }
}
namespace basl
{
  bool LRBTParser::replaceOne (LRParser const & start_lr_parser, int number, FreeTokenVector const & free_token_set, LRParser & lr_parser)
    {
      LRParserDeque lr_parser_set;
      lr_parser_set.push_back (start_lr_parser);
      while (! lr_parser_set.empty ())
      {
        // replace only if next token number is number 
        LRParser const & first_lr_parser = lr_parser_set.front ();
        TokenListIter p = first_lr_parser.token_iter;
        if (p->getNumber () == number && number != 0)
        {
          TokenListIter q = getNextToken (p, getLexState (first_lr_parser));
          TokenListIter r = insertTokens (token_set, q, p->getLoc (), free_token_set);
          for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
          {
            lr_parser = * i;
            lr_parser.token_iter = r;
            if (dfParse (lr_parser))
            {
              msg::replacingTokens (p->getLoc (), p->getLexeme (), 1, free_token_set);
              return true;
            }
          }
          // failed
          token_set.erase (r, q);
        }
        // parse next token
        LRParserDeque next_lr_parser_set;
        for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
        {
          lr_parser = * i;
          bfParse (lr_parser, next_lr_parser_set);
        }
        lr_parser_set.swap (next_lr_parser_set);
      }
      return false;
    }
}
namespace basl
{
  bool LRBTParser::moveSome (LRParser const & start_lr_parser, int max_move, int max_num, LRParser & lr_parser)
    {
      for (int num = 1; num <= max_num; ++ num)
      {
        LRParserDeque lr_parser_set;
        lr_parser_set.push_back (start_lr_parser);
        while (! lr_parser_set.empty ())
        {
          LRParser const & first_lr_parser = lr_parser_set.front ();
          TokenListIter p = first_lr_parser.token_iter;
          TokenListIter q = p;
          int cnt = 0;
          for (; cnt < num && q->getNumber () != 0; ++ cnt)
          {
            q = getNextToken (q, 0);
          }
          if (cnt != num)
          {
            break;
          }
          for (int num_move = 1; num_move <= max_move; ++ num_move)
          {
            TokenListIter t = q;
            for (cnt = 0; cnt < num_move && t->getNumber () != 0; ++ cnt)
            {
              t = getNextToken (t, 0);
            }
            if (cnt != num_move)
            {
              break;
            }
            TokenListIter r = moveTokens (token_set, p, q, t);
            for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
            {
              lr_parser = * i;
              lr_parser.token_iter = q;
              if (dfParse (lr_parser))
              {
                msg::movingTokens (p->getLoc (), p->getLexeme (), num_move, num, t->getLexeme ());
                return true;
              }
            }
            // failed, erase moved tokens
            token_set.erase (r, t);
          }
          // parse next token
          LRParserDeque next_lr_parser_set;
          for (LRParserDequeIter i = lr_parser_set.begin (); i != lr_parser_set.end (); ++ i)
          {
            lr_parser = * i;
            bfParse (lr_parser, next_lr_parser_set);
          }
          lr_parser_set.swap (next_lr_parser_set);
        }
      }
      return false;
    }
}
namespace basl
{
  bool LRBTParser::parse (int start_state, ErrorRec const & error_rec, SyntaxTree & tree)
    {
      assert (start_state < data.num_start_rules);
      LRParser start_lr_parser (start_state);
      int lex_state = getLexState (start_lr_parser);
      token_set.push_back (lexer.getNextToken (lex_state));
      start_lr_parser.token_iter = token_set.begin ();

      // maximum number of syntax errors (to avoid infinite fixes, specially for cgi version)
      int const max_errors = 30;
      int num_errors = 0;

      LRParser lr_parser (start_lr_parser);
      done = false;
      bool has_errors = false;
      for (;;)
      {
        // try depth first parse
        if (! dfParse (lr_parser))
        {
          // syntax error
          has_errors = true;
          ++ num_errors;
          Token token = * lr_parser.token_iter;
          msg::syntaxError (token.getLoc (), token.getLexeme ());
          RecCmdPtrDeque const & rec_set = error_rec.getRecCmdSet ();
          if (num_errors == max_errors)
          {
            msg::syntaxErrorLimitReached (token.getLoc ());
            break;
          }
          else if (std::find_if (rec_set.begin (), rec_set.end (), CanRecover (* this, start_lr_parser, lr_parser)) == rec_set.end ())
          {
            msg::unableToRecover (token.getLoc ());
            break;
          }
        }
        if (done)
        {
          break;
        }
        // start parser is now latest trial parser, no need for any previous tokens 
        start_lr_parser = lr_parser;
        token_set.erase (token_set.begin (), start_lr_parser.token_iter);
      }
      if (has_errors)
      {
        return false;
      }
      tree = lr_parser.tree;
      return true;
    }
}
namespace basl
{
  LRBTParser::~ LRBTParser ()
         {}
}
#undef LZZ_INLINE
