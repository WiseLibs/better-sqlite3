// smtc_TranslateVdfDataInit.cpp
//

#include "smtc_TranslateVdfDataInit.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_CopyInit.h"
#include "smtc_CreateCopyInit.h"
#include "smtc_CreateDirectInit.h"
#include "smtc_DirectInit.h"
#include "smtc_GetVdfDataId.h"

// gram
#include "gram_CharBlock.h"
#include "gram_Lexer.h"
#include "gram_MacroFilter.h"
#include "gram_RemoveQuotes.h"
#include "gram_TokenNumber.h"

// util
#include "util_GetSpaces.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  void tokenizeBlock (gram::Block const & block, basl::TokenDeque & token_set);
}
namespace
{
  gram::Block translateBlock (gram::Block const & block);
}
namespace
{
  struct TranslateBlock
  {
    gram::Block operator () (gram::Block const & block) const;
  public:
    explicit TranslateBlock ();
    ~ TranslateBlock ();
  };
}
namespace
{
  void tokenizeBlock (gram::Block const & block, basl::TokenDeque & token_set)
  {
    // just get tokens with lexer
    gram::Lexer lexer (block.toString (), block.getLoc ());
    // may take up more than one line
    for (;;)
    {
      basl::Token token;
      if (lexer.getNextToken (token))
      {
        if (token.getNumber () == gram::EOT)
        {
          break;
        }
        do
        {
          token_set.push_back (token);
        }
        while (lexer.getNextToken (token));
      }
    }

    /* to macro subsitute tokens ...
    // lex block and run through macro filter -- do not preprocess as '$' will be interpreted as start
    // of directive (if starting line)!
    gram::Lexer lexer (block.toString (), block.getLoc ());
    gram::FileMacroFilter filter (token_set);
    // may take up more than one line
    for (;;)
    {
      basl::Token token;
      if (lexer.getNextToken (token))
      {
        if (token.getNumber () == gram::EOT)
        {
          break;
        }
        do
        {
          filter.next (token);
        }
        while (lexer.getNextToken (token));
      }
    }
    filter.flush ();
    */
  }
}
namespace
{
  gram::Block translateBlock (gram::Block const & block)
  {
    basl::TokenDeque token_set;
    tokenizeBlock (block, token_set);
    gram::CharBlock res_block (block.getLoc ());
    if (! token_set.empty ())
    {
      int last_line = token_set.front ().getLoc ().getLine ();
      for (basl::TokenDequeConstIter beg = token_set.begin (), end = token_set.end (); beg != end; ++ beg)
      {
        // keep lines same for debugger
        util::Loc const & loc = beg->getLoc ();
        if (loc.getLine () != last_line)
        {
          res_block.append ('\n');
          res_block.append (util::getSpaces (beg->getLoc ().getColumn () - 1));
          last_line = loc.getLine ();
        }
        else if (beg->hasSpaceBefore ())
        {
          res_block.append (' ');
        }
        if (beg->getNumber () == gram::DOLLAR_TOKEN && ! (beg + 1 == end || beg + 2 == end) &&
            (beg + 1)->getNumber () == gram::IDENT_TOKEN && (beg + 2)->getNumber () == gram::LITERAL_STRING_TOKEN)
        {
          res_block.append (getVdfDataId ((beg + 1)->getLexeme ().c_str (), gram::removeQuotes ((beg + 2)->getLexeme ())));
          beg += 2;
          if (beg + 1 == end || (beg + 1)->getNumber () != gram::LPAREN_TOKEN)
          {
            res_block.append (" ()");
          }
        }
        else if (beg->getNumber () == gram::IDENT_TOKEN && ! (beg + 1 == end || beg + 2 == end) &&
            (beg + 1)->getNumber () == gram::DOLLAR_TOKEN && (beg + 2)->getNumber () == gram::LITERAL_STRING_TOKEN)
        {
          res_block.append (getVdfDataId (beg->getLexeme ().c_str (), gram::removeQuotes ((beg + 2)->getLexeme ())));
          beg += 2;
          if (beg + 1 == end || (beg + 1)->getNumber () != gram::LPAREN_TOKEN)
          {
            res_block.append (" ()");
          }
        }
        else
        {
          res_block.append (beg->getLexeme ().c_str ());
        }
      }
    }
    return res_block;
  }
}
namespace
{
  LZZ_INLINE gram::Block TranslateBlock::operator () (gram::Block const & block) const
  {
    return translateBlock (block);
  }
}
namespace
{
  LZZ_INLINE TranslateBlock::TranslateBlock ()
                     {}
}
namespace
{
  TranslateBlock::~ TranslateBlock ()
                     {}
}
namespace smtc
{
  InitPtr translateVdfDataInit (InitPtr const & init)
  {
    InitPtr res_init;
    if (init->isCopy ())
    {
      CopyInit const & copy_init = static_cast <CopyInit const &> (* init);
      gram::Block res_block = translateBlock (copy_init.getBlock ());
      res_init = createCopyInit (copy_init.getLoc (), res_block);
    }
    else
    {
      DirectInit const & direct_init = static_cast <DirectInit const &> (* init);
      gram::BlockVector const & block_set = direct_init.getBlockSet ();
      gram::BlockVector res_block_set;
      std::transform (block_set.begin (), block_set.end (), std::back_inserter (res_block_set), TranslateBlock ());
      res_init = createDirectInit (direct_init.getLoc (), res_block_set);
    }
    return res_init;
  }
}
#undef LZZ_INLINE
