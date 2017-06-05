// smtc_PrintUsingDir.h
//

#ifndef LZZ_smtc_PrintUsingDir_h
#define LZZ_smtc_PrintUsingDir_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_SectionKind.h"
#include "smtc_UsingDirPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printUsingDir (FilePtr const & file, SectionKind skind, UsingDirPtr const & using_dir, NsPtr const & ns);
}
namespace smtc
{
  void printUsingDir (FilePtr const & file, SectionKind skind, UsingDirPtr const & using_dir);
}
#undef LZZ_INLINE
#endif
