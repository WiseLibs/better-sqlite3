// gram_Prep.cpp
//

#include "gram_Prep.h"
// gram
#include "gram_BlockTable.h"
#include "gram_BuildMacro.h"
#include "gram_CheckMacroRepSet.h"
#include "gram_CreateFileStat.h"
#include "gram_DirTable.h"
#include "gram_DiscardRestOfLine.h"
#include "gram_EvalHashIfExpr.h"
#include "gram_FileStat.h"
#include "gram_FindIncludeFile.h"
#include "gram_GetIdent.h"
#include "gram_IsMacroSame.h"
#include "gram_KeywordTable.h"
#include "gram_LexBlockToken.h"
#include "gram_LexDefineLine.h"
#include "gram_LexPPNumber.h"
#include "gram_LexRestOfLine.h"
#include "gram_Macro.h"
#include "gram_MacroTable.h"
#include "gram_Message.h"
#include "gram_RemoveQuotes.h"
#include "gram_TokenNumber.h"

// semantic
#include "smtc_File.h"
#include "smtc_PrintCode.h"

// config
#include "conf_Config.h"

// util
#include "util_Exception.h"
#include "util_FileOp.h"
#include "util_FilenameTable.h"
#include "util_GetIdent.h"
#include "util_GetNextWord.h"
#include "util_GetRealPath.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  bool lexIncludeLine (Lexer & lexer, util::Loc const & dir_loc, util::Ident const & dir_name, bool live, util::Loc & name_loc, util::String & name);
}
namespace
{
  bool lexIfLine (Lexer & lexer, util::Loc const & dir_loc, util::Ident const & dir_name, bool live);
}
namespace
{
  bool lexIfdefLine (Lexer & lexer, util::Loc const & dir_loc, util::Ident const & dir_name, util::Ident & macro_name);
}
namespace
{
  bool isLineNum (basl::Token & token, int & line_num);
}
namespace
{
  bool isLineNumAndFilename (basl::Token & token1, basl::Token & token2, int & line_num, util::String & filename);
}
namespace
{
  bool lexLineLine (Lexer & lexer, util::Loc const & dir_loc, bool live, int & line_num, util::String & filename);
}
namespace
{
  util::String remFileDelimiters (util::String const & str, bool & is_system);
}
namespace
{
  gram::Block readFileBlock (Lexer & lexer);
}
namespace
{
  bool checkPragmaInlOptions (util::Ident const & dir, basl::TokenVectorConstIter beg, basl::TokenVectorConstIter end, bool & flag, util::String & ext);
}
namespace
{
  bool isYes (util::Ident const & ident);
}
namespace
{
  bool isNo (util::Ident const & ident);
}
namespace gram
{
  Prep::Prep (util::String const & name, smtc::Output * output, bool insert_all)
    : output (output), macro_filter (out_set), lexing_line (false), insert_all (insert_all), from_file (true), real_mode (false)
    {
      // get filename
      util::Filename filename;
      if (! util::getFilename (name, filename))
      {
        // can't continue, must throw exception 
        msg::fileOpenError (util::Loc (), name.c_str ());
        throw util::Exception ();
      }

      // push main file on file stack
      fs_stack.push_back (createFileStat (filename, true));

      // get auto include files (open as if it was #include'd on first line)
      util::StringVector const & auto_filename_set = conf::getOptionValue (conf::opt_ai_filename);
      for (util::StringVectorConstIter beg = auto_filename_set.begin (), end = auto_filename_set.end (); beg != end; ++ beg)
      {
        openIncludeFile (util::getIdent ("include"), util::Loc (filename, 1, 1), false, * beg, false);
      }
    }
}
namespace gram
{
  Prep::Prep (util::String const & str, util::Loc const & loc)
    : output (0), macro_filter (out_set), lexing_line (false), insert_all (false), from_file (false), real_mode (false)
    {
      // push input on file stack
      fs_stack.push_back (createFileStat (str, loc, true));
    }
}
namespace gram
{
  bool Prep::fromFile () const
    {
      return from_file;
    }
}
namespace gram
{
  Lexer & Prep::getLexer () const
    {
      return fs_stack.back ()->lexer;
    }
}
namespace gram
{
  basl::TokenDeque & Prep::getPendingTokens ()
    {
      return out_set;
    }
}
namespace gram
{
  void Prep::setRealMode (bool mode)
    {
      real_mode = mode;
    }
}
namespace gram
{
  bool Prep::hasPendingToken (basl::Token & token)
    {
      bool result = false;
      if (! out_set.empty ())
      {
        result = true;
        token = out_set.front ();
        out_set.pop_front ();
        // check if keyword
        int number;
        if (token.getNumber () == IDENT_TOKEN && isKeyword (token.getLexeme (), number))
        {
          token.setNumber (number);
        }
      }
      return result;
    }
}
namespace gram
{
  void Prep::ungetToken (basl::Token const & token)
    {
      out_set.push_front (token);
    }
}
namespace gram
{
  basl::Token Prep::getNextToken ()
    {
      basl::Token token;
      // otherwise preprocess until token available
      while (out_set.empty ())
      {
        if (lexing_line && fs_stack.back ()->lexer.getNextToken (token))
        {
          macro_filter.next (token);
        }
        else
        {
          // not lexing line
          lexing_line = false;
          // current file stat and if stat
          FileStat & fs = * fs_stack.back ();
          IfStat & is = fs.is_stack.back ();
          // get next non blank line
          while (! fs.lexer.getNextToken (token))
          {
          }
          // check end of file
          int number = token.getNumber ();
          if (number == EOT)
          {
            // should be outside any #if blocks
            if (is.ss != NONE_SS)
            {
              msg::missingEndif (is.loc);
            }
            // check if file contains an include guard
            else if (fs.guard_macro.isSet () && fs.status == FILE_ENDX)
            {
              guard_map [fs.realname] = fs.guard_macro;
            }
            fs_stack.pop_back ();
            if (fs_stack.empty ())
            {
              // no more tokens 
              macro_filter.flush ();
              out_set.push_back (token);
            }
          }
          // if not hash then it's code
          else if (! (number == HASH_TOKEN || number == DOLLAR_TOKEN))
          {
            // in body of file
            fs.status = FILE_BODY;
            // if inserting file and live send token through macro filter and lex rest of line
            if ((real_mode || fs.insert)  && is.rs == ON_RS)
            {
              macro_filter.next (token);
              lexing_line = true;
            }
            // otherwise discard line
            else
            {
              discardRestOfLine (fs.lexer);
            }
          }
          // is it a # followed by a newline?
          else if (! fs.lexer.getNextToken (token))
          {
            // it is, ignore line and do nothing
          }
          // token must be an identifier
          else if (token.getNumber () != IDENT_TOKEN)
          {
            // warn and continue with next line
            msg::invalidDir (token.getLoc ());
            discardRestOfLine (fs.lexer);
          }
          // identifier is a directive
          else
          {
            // directive name and location
            util::Loc const & dir_loc = token.getLoc ();
            util::Ident const & dir_name = token.getLexeme ();
            DirKind dir_kind;
            if (! isDir (dir_name, dir_kind))
            {
              msg::unknownDir (dir_loc, dir_name);
              discardRestOfLine (fs.lexer);
            }
            // we don't permit a special lzz directive in real mode
            else if (real_mode && dir_kind >= INSERT_DIR)
            {
              msg::dirInInvalidContext (dir_loc, dir_name);
              discardRestOfLine (fs.lexer);
            }
            // number is number is either HASH or DOLLAR
            else
            {
              switch (dir_kind)
              {
                // defiene
                case DEFINE_DIR:
                {
                  prepDefine (dir_loc);
                  break;
                }
                // include and insert
                case INCLUDE_DIR:
                case INSERT_DIR:
                {
                  prepInclude (dir_loc, dir_name, dir_kind == INSERT_DIR);
                  break;
                }
                // if
                case IF_DIR:
                {
                  prepIf (dir_loc, dir_name);
                  break;
                }
                // ifdef and ifndef
                case IFNDEF_DIR:
                case IFDEF_DIR:
                {
                  prepIfdef (dir_loc, dir_name, dir_kind == IFNDEF_DIR);
                  break;
                }
                // elif
                case ELIF_DIR:
                {
                  prepElif (dir_loc, dir_name);
                  break;
                }
                // else
                case ELSE_DIR:
                {
                  prepElse (dir_loc, dir_name);
                  break;
                }
                // endif
                case ENDIF_DIR:
                {
                  prepEndif (dir_loc, dir_name);
                  break;
                }
                // undef
                case UNDEF_DIR:
                {
                  prepUndef (dir_loc, dir_name);
                  break;
                }
                // line
                case LINE_DIR:
                {
                  prepLine (dir_loc);
                  break;
                }
                // error
                case ERROR_DIR:
                {
                  prepError (dir_loc);
                  break;
                }
                // pragma
                case PRAGMA_DIR:
                {
                  prepPragma (dir_loc);
                  break;
                }
                // warning
                case WARNING_DIR:
                {
                  prepWarning (dir_loc);
                  break;
                }
                // hdr or header
                case HDR_DIR:
                {
                  prepHdrBlock (dir_loc, dir_name);
                  break;
                }
                // src or source
                case SRC_DIR:
                {
                  prepSrcBlock (dir_loc, dir_name);
                  break;
                }
                // inl or inline
                case INL_DIR:
                {
                  prepInlBlock (dir_loc, dir_name);
                  break;
                }
                // tpl or template
                case TPL_DIR:
                {
                  prepTplBlock (dir_loc, dir_name);
                  break;
                }
                // tnl or template_inline
                case TNL_DIR:
                {
                  prepTnlBlock (dir_loc, dir_name);
                  break;
                }
              }
            }
          }
        }
      }
      token = out_set.front ();
      out_set.pop_front ();
      // check if keyword
      int number;
      if (token.getNumber () == IDENT_TOKEN && isKeyword (token.getLexeme (), number))
      {
        token.setNumber (number);
      }
      return token;
    }
}
namespace gram
{
  void Prep::prepDefine (util::Loc const & dir_loc)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in body
      fs.status = FILE_BODY;
      // lex line if not successful remaining tokens on line discarded
      util::Loc loc;
      util::Ident name;
      bool is_func = false;
      util::IdentVector param_set;
      bool var = false;
      basl::TokenVector rep_set;
      if (lexDefineLine (fs.lexer, false, dir_loc, loc, name, is_func, param_set, var, rep_set))
      {
        // add macro (and check replacement set) only if in true #if
        if (is.rs == ON_RS && checkMacroRepSet (is_func, param_set, var, rep_set))
        {
          // check if already defined
          MacroPtr macro;
          if (isMacro (name, macro))
          {
            // check if redefined
            if (! isMacroSame (macro, is_func, param_set, var, rep_set))
            {
              // warn and ignore this definition
              msg::macroRedefined (loc, name, macro->getLoc ());
            }
          }
          else
          {
            // build macro and add it to table
            macro = buildMacro (loc, name, is_func, param_set, var, rep_set);
            addMacro (macro);
          }
        }
      }
    }
}
namespace gram
{
  bool Prep::hasPragmaOnce (char const * realname)
    {
      return pragma_once_set.count (realname) == 1;
    }
}
namespace gram
{
  bool Prep::hasGuard (char const * realname)
    {
      GuardMapIter iter = guard_map.find (realname);
      return iter != guard_map.end () && isMacro (iter->second);
    }
}
namespace gram
{
  void Prep::openIncludeFile (util::Ident const & dir_name, util::Loc const & name_loc, bool insert, util::String const & name, bool is_system)
    {
      util::String fullname;
      // find file
      if (! findIncludeFile (name_loc.getFilename ().getName (), name, is_system, fullname))
      {
        msg::hashIncludeFileNotFound (name_loc, dir_name, name, is_system);
        return;
      }
      // get filename
      util::Filename filename;
      if (! util::getFilename (fullname, filename))
      {
        // no need to throw exception, just ignore this file
        msg::fileOpenError (name_loc, fullname.c_str ());
        return;
      }
      // check if already included file with pragma once
      char const * realname = filename.getRealName ();
      if (! (hasPragmaOnce (realname) || hasGuard (realname)))
      {
        // pause current lexer and push new file stat
        fs_stack.back ()->lexer.pause ();
        fs_stack.push_back (createFileStat (filename, insert || insert_all));
      }
    }
}
namespace gram
{
  void Prep::prepInclude (util::Loc const & dir_loc, util::Ident const & dir_name, bool insert)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in body
      fs.status = FILE_BODY;
      // lex line
      util::Loc name_loc;
      util::String name;
      if (lexIncludeLine (fs.lexer, dir_loc, dir_name, is.rs == ON_RS, name_loc, name))
      {
        // if running cgi version we don't want to show any #include files!
#ifdef CGI_BUILD
        msg::hashIncludeDisabled (dir_loc);
#else
        bool is_system = false;
        name = remFileDelimiters (name, is_system);
        openIncludeFile (dir_name, name_loc, insert, name, is_system);
#endif
      }
    }
}
namespace gram
{
  void Prep::prepIf (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in file body
      fs.status = FILE_BODY;
      // get next read state
      int rs = OFF_RS;
      try
      {
        bool live = (is.rs == ON_RS);
        if (lexIfLine (fs.lexer, dir_loc, dir_name, live))
        {
          // live and #if true
          rs = ON_RS;
        }
        else if (live)
        {
          // live and #if false
          rs = WAIT_RS;
        }
      }
      catch (util::Exception const & e)
      {
      }
      // push next if state
      fs.is_stack.push_back (IfStat (dir_loc, rs, IF_SS, false));
    }
}
namespace gram
{
  void Prep::prepIfdef (util::Loc const & dir_loc, util::Ident const & dir_name, bool is_ifndef)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in file body
      fs.status = FILE_BODY;
      // get next read state
      int rs = OFF_RS;
      bool guard = false;
      // lex line
      util::Ident macro_name;
      if (lexIfdefLine (fs.lexer, dir_loc, is_ifndef ? "ifndef" : "ifdef", macro_name) && is.rs == ON_RS)
      {
        bool is_macro = isMacro (macro_name);
        if (is_ifndef)
        {
          rs = is_macro ? WAIT_RS : ON_RS;
          // check if file include guard
          if (fs.status == FILE_START)
          {
            guard = true;
            fs.guard_macro = macro_name;
          }
        }
        else
        {
          rs = is_macro ? ON_RS : WAIT_RS;
        }
      }
      // push next if state
      fs.is_stack.push_back (IfStat (dir_loc, rs, IF_SS, guard));
    }
}
namespace gram
{
  void Prep::prepElif (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // ignore line if out of order
      if (is.ss != IF_SS)
      {
        msg::elifWithoutIf (dir_loc);
        discardRestOfLine (fs.lexer);
        return;
      }
      // in file body
      fs.status = FILE_BODY;
      // get next read state
      int rs = OFF_RS;
      try
      {
        bool live = (is.rs == WAIT_RS);
        if (lexIfLine (fs.lexer, dir_loc, dir_name, live))
        {
          // live and #elif true
          rs = ON_RS;
        }
        else if (live)
        {
          // live and #elif false
          rs = WAIT_RS;
        }
      }
      catch (util::Exception const & e)
      {
      }
      is.rs = rs;
      is.guard = false;
    }
}
namespace gram
{
  void Prep::prepElse (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in body
      fs.status = FILE_BODY;
      // no characters should be remaining on line
      basl::Token token;
      if (fs.lexer.getNextToken (token))
      {
        msg::extraTokensFollowingDir (token.getLoc (), dir_name);
        discardRestOfLine (fs.lexer);
      }
      // skip line if directive is out of order
      if (is.ss != IF_SS)
      {
        msg::elseWithoutIf (dir_loc);
        return;
      }
      // if waiting then if state is live, otherwise off
      is.rs = (is.rs == WAIT_RS) ? ON_RS : OFF_RS;
      is.ss = ELSE_SS;
      is.guard = false;
    }
}
namespace gram
{
  void Prep::prepEndif (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // no characters should be remaining on line
      basl::Token token;
      if (fs.lexer.getNextToken (token))
      {
        msg::extraTokensFollowingDir (token.getLoc (), dir_name);
        discardRestOfLine (fs.lexer);
      }
      // skip line if directive is out of order
      if (is.ss == NONE_SS)
      {
        msg::endifWithoutIf (dir_loc);
        return;
      }
      // end of include guard?
      if (is.guard)
      {
        // end of include guard
        fs.status = FILE_ENDX;
      }
      else
      {
        // otherwise in body
        fs.status = FILE_BODY;
      }
      // pop if state
      fs.is_stack.pop_back ();
    }
}
namespace gram
{
  void Prep::prepUndef (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in file body
      fs.status = FILE_BODY;
      // lex line
      util::Ident macro_name;
      if (lexIfdefLine (fs.lexer, dir_loc, "undef", macro_name) && is.rs == ON_RS)
      {
        // delete macro if defined
        if (isMacro (macro_name))
        {
          delMacro (macro_name);
        }
      }
    }
}
namespace gram
{
  void Prep::prepLine (util::Loc const & dir_loc)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in body
      fs.status = FILE_BODY;
      // lex line
      int line_num;
      util::String filename;
      if (lexLineLine (fs.lexer, dir_loc, is.rs == ON_RS, line_num, filename))
      {
        if (! filename.empty ())
        {
          // if not absolute use path of current file 
          if (! util::file_op::isAbsolute (filename))
          {
            filename = util::file_op::join (util::file_op::getPath (fs.lexer.getFilename ().getName ()), filename);
          }
          fs.lexer.setLine (line_num, util::storeFilename (filename));
        }
        else
        {
          fs.lexer.setLine (line_num);
        }
      }
    }
}
namespace gram
{
  void Prep::prepError (util::Loc const & dir_loc)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in body
      fs.status = FILE_BODY;
      // get rest of line
      util::String str;
      fs.lexer.discardWs ();
      fs.lexer.getRestOfLine (str);
      if (is.rs == ON_RS)
      {
        // fatal error
        msg::hashError (dir_loc, str);
        throw util::Exception ();
      }
    }
}
namespace gram
{
  void Prep::prepPragma (util::Loc const & dir_loc)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in body
      fs.status = FILE_BODY;
      // lex line
      basl::TokenVector token_set;
      lexRestOfLine (fs.lexer, token_set);
      // consider only if live
      if (is.rs == ON_RS && ! token_set.empty ())
      {
        basl::TokenVectorConstIter beg = token_set.begin (), end = token_set.end ();
        bool lzz_pragma = false;
        if (beg->getLexeme () == lzz_ident)
        {
          lzz_pragma = true;
          ++ beg;
          if (beg == end)
          {
            msg::missingPragmaName (dir_loc);
            return;
          }
        }
        util::Ident name = beg->getLexeme ();
#ifdef PRL_BUILD
        // support the old 'use-inl', 'use-tpl', 'use-tnl' pragma options
        if (name == use_ident && ! (beg + 1 == end || beg + 2 == end) && (beg + 1)->getNumber () == MINUS_TOKEN)
        {
          beg += 2;
          name = beg->getLexeme ();
        }
#endif
        if (name == inl_ident || name == tpl_ident || name == tnl_ident)
        {
          bool flag = true;
          util::String ext;
          if (checkPragmaInlOptions (name, beg + 1, end, flag, ext))
          {
            conf::setUseFile (name, flag, ext);
          }
        }
        else if (name == once_ident)
        {
          // remember filename in pragma once set
          pragma_once_set.insert (fs.realname);
        }
        // this is for PRL only
#ifdef PRL_BUILD
        else if (name == tplsrc_ident)
        {
          // output template code to source file instead of to template or header file
          conf::setTplSrc ();
        }
#endif
        else if (name == prep_block_ident)
        {
          // preprocess blocks, check optional flag
          bool flag = true;
          if (beg + 1 != end)
          {
            ++ beg;
            util::Ident flag_ident = beg->getLexeme ();
            if (isNo (flag_ident))
            {
              flag = false;
            }
            else if (! isYes (flag_ident))
            {
              msg::invalidPragmaFlag (beg->getLoc ());
            }
          }
          conf::setPrepBlock (flag);
        }
        else if (lzz_pragma)
        {
          msg::invalidPragma (beg->getLoc (), name);
          return;
        }
      }
    }
}
namespace gram
{
  void Prep::prepWarning (util::Loc const & dir_loc)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // in body
      fs.status = FILE_BODY;
      // get rest of line
      util::String str;
      fs.lexer.discardWs ();
      fs.lexer.getRestOfLine (str);
      if (is.rs == ON_RS)
      {
        // not a fatal error 
        msg::hashWarning (dir_loc, str);
      }
    }
}
namespace gram
{
  Block Prep::prepFileBlock (util::Loc const & dir_loc, util::Ident dir_name)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      // in body
      fs.status = FILE_BODY;
      // no characters should be remaining on line
      basl::Token token;
      if (fs.lexer.getNextToken (token))
      {
        msg::extraTokensFollowingDir (token.getLoc (), dir_name);
        discardRestOfLine (fs.lexer);
      }
      // always read block
      return readFileBlock (fs.lexer);
    }
}
namespace gram
{
  void Prep::printFileBlock (Block const & block, smtc::FilePtr const & file, smtc::SectionKind skind)
    {
      // get current file stat and if state
      FileStat & fs = * fs_stack.back ();
      IfStat & is = fs.is_stack.back ();
      // print if live and block not empty
      if (is.rs == ON_RS && ! block.isEmpty ())
      {
        smtc::printBlock (file, skind, block);
      }
    }
}
namespace gram
{
  void Prep::prepHdrBlock (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      Block block = prepFileBlock (dir_loc, dir_name);
      if (output)
      {
        smtc::FilePtr file = output->getHdrFile ();
        printFileBlock (block, file, smtc::USER_SECTION);
      }
    }
}
namespace gram
{
  void Prep::prepSrcBlock (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      Block block = prepFileBlock (dir_loc, dir_name);
      if (output)
      {
        smtc::FilePtr file = output->getSrcFile ();
        printFileBlock (block, file, smtc::USER_SECTION);
      }
    }
}
namespace gram
{
  void Prep::prepInlBlock (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      Block block = prepFileBlock (dir_loc, dir_name);
      if (output)
      {
        if (conf::getOptionValue (conf::opt_inl_inl))
        {
          // inline code goes to both header and source files
          printFileBlock (block, output->getHdrFile (), smtc::INLINE_USER_SECTION);
          printFileBlock (block, output->getSrcFile (), smtc::INLINE_USER_SECTION);
        }
        else
        {
          // output to header file if not creating inline file
          smtc::FilePtr file = conf::getOptionValue (conf::opt_inl) ? output->getInlFile () : output->getHdrFile ();
          printFileBlock (block, file, smtc::USER_SECTION);
        }
      }
    }
}
namespace gram
{
  void Prep::prepTplBlock (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      Block block = prepFileBlock (dir_loc, dir_name);
      if (output)
      {
        // output to header file if not creating template file
        smtc::FilePtr file = conf::getOptionValue (conf::opt_tpl) ? output->getTplFile () : output->getHdrFile ();
        printFileBlock (block, file, smtc::USER_SECTION);
      }
    }
}
namespace gram
{
  void Prep::prepTnlBlock (util::Loc const & dir_loc, util::Ident const & dir_name)
    {
      Block block = prepFileBlock (dir_loc, dir_name);
      if (output)
      {
        // output to header file if not creating tempalte inline file
        smtc::FilePtr file = conf::getOptionValue (conf::opt_tnl) ? output->getTnlFile () : output->getHdrFile ();
        printFileBlock (block, file, smtc::USER_SECTION);
      }
    }
}
namespace
{
  bool lexIncludeLine (Lexer & lexer, util::Loc const & dir_loc, util::Ident const & dir_name, bool live, util::Loc & name_loc, util::String & name)
  {
    util::Loc loc;
    basl::Token token;
    if (! lexer.getNextToken (INCLUDE_LEX_STATE, loc, token))
    {
      msg::missingHashIncludeFilename (dir_loc, dir_name);
      return false;
    }
    // find filename string, line should be either a string or some number of tokens (not starting with a string)
    if (token.getNumber () == LITERAL_STRING_TOKEN)
    {
      basl::Token next_token;
      if (lexer.getNextToken (next_token))
      {
        msg::extraTokensFollowingDir (next_token.getLoc (), dir_name);
        discardRestOfLine (lexer);
      }
      if (live)
      {
        name_loc = token.getLoc ();
        name = token.getLexeme ().c_str ();
      }
      else
      {
        return false;
      }
    }
    // if not live discard remaining tokens
    else if (! live)
    {
      discardRestOfLine (lexer);
      return false;
    }
    // otherwise replace macros in token set
    else
    {
      basl::TokenDeque out_set;
      FileMacroFilter filter (out_set);
      basl::TokenVector token_set;
      token_set.push_back (token);
      lexRestOfLine (lexer, token_set);
      filter.next (token_set);
      // could be either a literal string or a '<' followed by some number of tokens then '>'
      // a system file must have at least three tokens
      if (out_set.size () >= 3 && out_set.front ().getNumber () == LT_TOKEN && out_set.back ().getNumber () == GT_TOKEN)
      {
        name_loc = token.getLoc ();
        // concat all tokens to get file string
        for (basl::TokenDequeConstIter beg = out_set.begin (), end = out_set.end (); beg != end; ++ beg)
        {
          name += (* beg).getLexeme ().c_str ();
        }
      }
      // a user file cannot be a wide string literal
      else if (out_set.size () == 1 && out_set.front ().getNumber () == LITERAL_STRING_TOKEN)
      {
        name_loc = token.getLoc ();
        name = out_set.front ().getLexeme ().c_str ();
      }
      // otherwise invalid file after macro expansion
      else
      {
        util::Loc const & loc = token.getLoc ();
        if (out_set.empty ())
        {
          msg::missingHashIncludeFilenameAfterMacroSub (loc, dir_name);
        }
        else
        {
          msg::invalidIncludeFilenameAfterMacroSub (loc, dir_name);
        }
        return false;
      }
    }
    return true;
  }
}
namespace
{
  bool lexIfLine (Lexer & lexer, util::Loc const & dir_loc, util::Ident const & dir_name, bool live)
  {
    // read all tokens on line
    bool result = false;
    util::Loc eol_loc;
    basl::TokenVector token_set;
    lexRestOfLine (lexer, eol_loc, token_set);
    if (token_set.empty ())
    {
      msg::missingHashIfTokens (dir_loc, dir_name);
    }
    // evaluate expr only if live
    else if (live)
    {
      // translate macros
      basl::TokenDeque in_set;
      HashIfMacroFilter if_filter (in_set);
      if_filter.next (token_set);
      if_filter.flush ();
      // warn if empty after macro translation 
      if (in_set.empty ())
      {
        msg::missingHashIfTokensAfterMacroSub (token_set.front ().getLoc (), dir_name);
      }
      else
      {
        result = evalHashIfExpr (dir_name, eol_loc, in_set);
      }
    }
    return result;
  }
}
namespace
{
  bool lexIfdefLine (Lexer & lexer, util::Loc const & dir_loc, util::Ident const & dir_name, util::Ident & macro_name)
  {
    util::Loc loc;
    basl::Token token;
    if (! lexer.getNextToken (loc, token))
    {
      msg::missingMacroIdent (dir_loc, dir_name);
      return false;
    }
    else if (token.getNumber () != IDENT_TOKEN)
    {
      msg::invalidMacroIdent (loc, dir_name);
      discardRestOfLine (lexer);
      return false;
    }
    else
    {
      macro_name = token.getLexeme ();
      // no tokens should be remaining on line
      if (lexer.getNextToken (loc, token))
      {
        msg::extraTokensFollowingDir (loc, dir_name);
        discardRestOfLine (lexer);
      }
    }
    return true;
  }
}
namespace
{
  bool isLineNum (basl::Token & token, int & line_num)
  {
    bool result = false;
    lexPPNumber (token);
    if (token.getNumber () == LITERAL_INT_TOKEN)
    {
      line_num = atoi (token.getLexeme ().c_str ());
      result = true;
    }
    return result;
  }
}
namespace
{
  bool isLineNumAndFilename (basl::Token & token1, basl::Token & token2, int & line_num, util::String & filename)
  {
    bool result = false;
    lexPPNumber (token1);
    if (token1.getNumber () == LITERAL_INT_TOKEN && token2.getNumber () == LITERAL_STRING_TOKEN)
    {
      line_num = atoi (token1.getLexeme ().c_str ());
      filename = removeQuotes (token2.getLexeme ());
      result = true;
    }
    return result;
  }
}
namespace
{
  bool lexLineLine (Lexer & lexer, util::Loc const & dir_loc, bool live, int & line_num, util::String & filename)
  {
    bool result = false;
    // read remaining tokens on line
    basl::TokenVector token_set;
    lexRestOfLine (lexer, token_set);
    if (token_set.empty ())
    {
      msg::missingHashLineTokens (dir_loc);
    }
    else if (live)
    {
      if (token_set.size () == 1 && isLineNum (token_set [0], line_num) ||
          token_set.size () == 2 && isLineNumAndFilename (token_set [0], token_set [1], line_num, filename))
      {
        result = true;
      }
      else
      {
        // replace macros
        basl::TokenDeque out_set;
        FileMacroFilter filter (out_set);
        filter.next (token_set);
        filter.flush ();
        if (out_set.size () == 1 && isLineNum (out_set [0], line_num) ||
            out_set.size () == 2 && isLineNumAndFilename (out_set [0], out_set [1], line_num, filename))
        {
          result = true;
        }
        else
        {
          util::Loc const & loc = token_set.front ().getLoc (); 
          if (out_set.empty ())
          {
            msg::missingHashLineTokensAfterMacroSub (loc);
          }
          else
          {
            msg::invalidHashLine (loc);
          }
        }
      }
    }
    return result;
  }
}
namespace
{
  util::String remFileDelimiters (util::String const & str, bool & is_system)
  {
    is_system = str [0] == '<';
    return str.substr (1, str.length () - 2);
  }
}
namespace
{
  gram::Block readFileBlock (Lexer & lexer)
  {
    using namespace util;
    char const * ws = " \t";
    Loc start_loc = lexer.getLoc ();
    CharBlock block (start_loc);
    for (;;)
    {
      Loc loc = lexer.getLoc ();
      String line; 
      if (! lexer.readLine (line))
      {
        msg::eofInFileBlock (start_loc);
        throw Exception ();
      }
      // check for terminating '#end' or '$end' ('%:' is a digraph for '#')
      String::size_type p = line.find_first_not_of (ws);
      if (p != String::npos && (line [p] == '$' || line [p] == '#' ||
              line [p] == '%' && p + 1 < line.length () && line [p + 1] == ':'))
      {
        if (line [p] == '%')
        {
          ++ p;
        }
        p = line.find_first_not_of (ws, p + 1);
        if (p != String::npos)
        {
          String::size_type q = line.find_first_of (ws, p);
          if (q == String::npos)
          {
            q = line.length ();
          }
          if (line.substr (p, q - p) == "end")
          {
            break;
          }
        }
      }
      block.appendLine (line);
    }
    return block;
  }
}
namespace
{
  bool checkPragmaInlOptions (util::Ident const & dir, basl::TokenVectorConstIter beg, basl::TokenVectorConstIter end, bool & flag, util::String & ext)
  {
    // flag
    if (beg != end)
    {
      util::Ident const & lexeme = beg->getLexeme ();
      if (isYes (lexeme))
      {
        flag = true;
      }
      else if (isNo (lexeme))
      {
        flag = false;
      }
      else
      {
        msg::invalidPragmaInlFlag (beg->getLoc (), dir, lexeme);
        return false;
      }
      if (++ beg != end)
      {
        if (beg->getNumber () == LITERAL_STRING_TOKEN)
        {
          ext = removeQuotes (beg->getLexeme ());
        }
        else
        {
          ext = beg->getLexeme ().c_str ();
        }
        if (++ beg != end)
        {
          // this is a warning
          msg::extraTokensFollowingDir (beg->getLoc (), pragma_ident);
        }
      }
    }
    return true;
  }
}
namespace
{
  bool isYes (util::Ident const & ident)
  {
    return ident == yes_ident || ident == on_ident;
  }
}
namespace
{
  bool isNo (util::Ident const & ident)
  {
    return ident == no_ident || ident == off_ident;
  }
}
#undef LZZ_INLINE
