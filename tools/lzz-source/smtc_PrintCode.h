// smtc_PrintCode.h
//

#ifndef LZZ_smtc_PrintCode_h
#define LZZ_smtc_PrintCode_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_SectionKind.h"

// gram
#include "gram_Block.h"
#include "gram_CharBlock.h"
#include "gram_PrettyPrintTokens.h"
#include "gram_TokenBlock.h"

// util
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printHashLine (FilePtr const & file, SectionKind skind, util::Loc const & loc);
}
namespace smtc
{
  void printOpenBrace (FilePtr const & file, SectionKind skind);
}
namespace smtc
{
  void printCloseBrace (FilePtr const & file, SectionKind skind, bool semi = false);
}
namespace smtc
{
  void printLine (FilePtr const & file, SectionKind skind, util::String const & line);
}
namespace smtc
{
  void printDir (FilePtr const & file, SectionKind skind, util::String const & line);
}
namespace smtc
{
  void printLine (FilePtr const & file, SectionKind skind, util::Loc const & loc, util::String const & line);
}
namespace smtc
{
  void printLine (FilePtr const & file, SectionKind skind, util::Loc const & loc, int offset, util::String const & line);
}
namespace smtc
{
  void printBlockAtLoc (smtc::FilePtr const & file, smtc::SectionKind skind, gram::Block const & block);
}
namespace smtc
{
  void printBlock (FilePtr const & file, SectionKind skind, gram::Block const & block);
}
namespace smtc
{
  void printEnclosedBlock (FilePtr const & file, SectionKind skind, gram::Block const & block);
}
#undef LZZ_INLINE
#endif
