// smtc_PrintNsOpen.h
//

#ifndef LZZ_smtc_PrintNsOpen_h
#define LZZ_smtc_PrintNsOpen_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_SectionKind.h"
#define LZZ_INLINE inline
namespace smtc
{
  int printNsOpen (FilePtr const & file, SectionKind skind, NsPtr const & ns);
}
namespace smtc
{
  int printNsOpenIfSet (FilePtr const & file, SectionKind skind, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
