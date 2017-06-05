// gram_PrettyPrintTokens.cpp
//

#include "gram_PrettyPrintTokens.h"
// std lib
#include <cstring>

// semantic
#include "smtc_PrintCode.h"
#include "smtc_File.h"

// gram
#include "gram_TokenNumber.h"

// util
#include "util_Filename.h"
#define LZZ_INLINE inline
namespace gram
{
  void prettyPrintTokens (smtc::FilePtr const & file, smtc::SectionKind skind, util::Loc const & start_loc, basl::TokenDeque const & tokens)
  {
    if (tokens.empty ())
    {
      return;
    }
    int line = start_loc.getLine ();
    // the column is always the column of single character delimiter
    int col = start_loc.getColumn () + 1;
    util::Filename filename = start_loc.getFilename ();
    bool ws_before = col == 1;
    bool last_macro = false;
    std::ostream & os = file->getStream (skind);
    for (basl::TokenDequeConstIter beg = tokens.begin (), end = tokens.end (); beg != end; ++ beg)
    {
      basl::Token const & token = * beg;
      if (token.getNumber () == EOT)
      {
        break;
      }
      util::Loc const & loc = token.getLoc ();
      // if filename is different print #line, if we jump more than a lot of lines also print a #line
      if (loc.getFilename () != filename || loc.getLine () < line || loc.getLine () - line > 32)
      {
        if (col != 1)
        {
          os << '\n';
        }
        printHashLine (file, skind, loc);
        // now we're at the line in the new file
        line = loc.getLine ();
        col = 1;
        ws_before = true;
        filename = loc.getFilename ();
      }
      else if (loc.getLine () > line)
      {
        for (int i = loc.getLine () - line; i > 0; -- i)
        {
          os << '\n';
          ++ line;
        }
        col = 1;
        ws_before = true;
      }
      if (loc.getColumn () > col)
      {
        for (int i = loc.getColumn () - col; i > 0; -- i)
        {
          os << ' ';
          ++ col;
        }
        ws_before = true;
      }
      if (! ws_before)
      {
        if (last_macro || token.fromMacro () || token.hasSpaceBefore ())
        {
          os << ' ';
          ++ col;
        }
      }
      os << token.getLexeme ().c_str ();
      col += strlen (token.getLexeme ().c_str ());
      ws_before = false;
      last_macro = token.fromMacro ();
    }
  }
}
namespace gram
{
  util::String prettyPrintTokensToString (basl::TokenDeque const & tokens)
  {
    util::String str;
    if (tokens.empty ())
    {
      return str;
    }
    util::Loc const & loc = tokens.front ().getLoc ();
    int line = loc.getLine ();
    util::Filename filename = loc.getFilename ();
    bool ws_before = true;
    bool last_macro = false;
    for (basl::TokenDequeConstIter beg = tokens.begin (), end = tokens.end (); beg != end; ++ beg)
    {
      basl::Token const & token = * beg;
      if (token.getNumber () == EOT)
      {
        break;
      }
      util::Loc const & loc = token.getLoc ();
      // if on differnet line, then output a single space
      if (! (loc.getFilename () == filename && loc.getLine () == line))
      {
        str += ' ';
        line = loc.getLine ();
        filename = loc.getFilename ();
        ws_before = true;
      }
      if (! ws_before)
      {
        if (last_macro || token.fromMacro () || token.hasSpaceBefore ())
        {
          str += ' ';
        }
      }
      str += token.getLexeme ().c_str ();
      ws_before = false;
      last_macro = token.fromMacro ();
    }
    return str;
  }
}
namespace gram
{
  void prettyPrintTokensToStream (std::ostream & os, basl::TokenDeque const & tokens)
  {
    if (tokens.empty ())
    {
      return;
    }
    util::Loc const & loc = tokens.front ().getLoc ();
    int line = loc.getLine ();
    util::Filename filename = loc.getFilename ();
    bool ws_before = true;
    bool last_macro = false;
    bool start_of_line = true;
    for (basl::TokenDequeConstIter beg = tokens.begin (), end = tokens.end (); beg != end; ++ beg)
    {
      basl::Token const & token = * beg;
      if (token.getNumber () == EOT)
      {
        break;
      }
      util::Loc const & loc = token.getLoc ();
      // if filename is different print #line, if we jump more than a lot of lines also print a #line
      if (! (loc.getFilename () == filename && loc.getLine () == line))
      {
        os << '\n';
        line = loc.getLine ();
        start_of_line = true;
        filename = loc.getFilename ();
        ws_before = false;
      }
      if (start_of_line)
      {
        for (int i = loc.getColumn () - 1; i > 0; -- i)
        {
          os << ' ';
        }
        start_of_line = false;
        ws_before = true;
      }
      if (! ws_before)
      {
        if (last_macro || token.fromMacro () || token.hasSpaceBefore ())
        {
          os << ' ';
        }
      }
      os << token.getLexeme ().c_str ();
      ws_before = false;
      last_macro = token.fromMacro ();
    }
    // always end with newline
    os << '\n';
  }
}
#undef LZZ_INLINE
