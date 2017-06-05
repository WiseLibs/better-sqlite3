// smtc_PrintCode.cpp
//

#include "smtc_PrintCode.h"
// semantic
#include "smtc_File.h"

// config
#include "conf_Config.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printHashLine (FilePtr const & file, SectionKind skind, util::Loc const & loc)
  {
    if (file->hasHashLines ())
    {
      util::Filename const & filename = loc.getFilename ();
      char const * name = conf::getOptionValue (conf::opt_expand_filename) ? filename.getRealName () : filename.getName ();
      file->getStream (skind) << "#line " << loc.getLine () << " \"" << name << '\"' << '\n';
    }
  }
}
namespace smtc
{
  void printOpenBrace (FilePtr const & file, SectionKind skind)
  {
    file->indent (skind) << '{' << '\n';
    file->incIndent (skind);
  }
}
namespace smtc
{
  void printCloseBrace (FilePtr const & file, SectionKind skind, bool semi)
  {
    file->decIndent (skind);
    std::ostream & os = file->indent (skind) << '}';
    if (semi)
    {
      os << ';';
    }
    os << '\n';
  }
}
namespace smtc
{
  void printLine (FilePtr const & file, SectionKind skind, util::String const & line)
  {
    file->indent (skind) << line << '\n';
  }
}
namespace smtc
{
  void printDir (FilePtr const & file, SectionKind skind, util::String const & line)
  {
    file->getStream (skind) << line << '\n';
  }
}
namespace smtc
{
  void printLine (FilePtr const & file, SectionKind skind, util::Loc const & loc, util::String const & line)
  {
    printHashLine (file, skind, loc);
    file->indent (skind) << line << '\n';
  }
}
namespace smtc
{
  void printLine (FilePtr const & file, SectionKind skind, util::Loc const & loc, int offset, util::String const & line)
  {
    printHashLine (file, skind, loc);
    file->indent (skind, offset) << line << '\n';
  }
}
namespace smtc
{
  void printBlockAtLoc (smtc::FilePtr const & file, smtc::SectionKind skind, gram::Block const & block)
  {
    if (block.isCharBlock ())
    {
      file->getStream (skind) << gram::CharBlock (block).c_str ();
    }
    else
    {
      gram::prettyPrintTokens (file, skind, block.getLoc (), gram::TokenBlock (block).getTokens ());
    }
  }
}
namespace smtc
{
  void printBlock (FilePtr const & file, SectionKind skind, gram::Block const & block)
  {
    printHashLine (file, skind, block.getLoc ());
    assert (block.isCharBlock ());
    file->getStream (skind) << gram::CharBlock (block).c_str ();
  }
}
namespace smtc
{
  void printEnclosedBlock (FilePtr const & file, SectionKind skind, gram::Block const & block)
  {
    util::Loc const & loc = block.getLoc ();
    printHashLine (file, skind, loc);
    // print opening brace at same column location
    int col = block.getLoc ().getColumn ();
    std::ostream & os = file->indentExactly (skind, col - 1) << '{';
    printBlockAtLoc (file, skind, block);
    // may be a character or token block 
    if (block.isCharBlock ())
    {
      os << '}' << '\n';
    }
    else
    {
      os << '\n';
      file->indent (skind) << '}' << '\n';
    }
  }
}
#undef LZZ_INLINE
