// smtc_PrintNsClose.h
//

#ifndef LZZ_smtc_PrintNsClose_h
#define LZZ_smtc_PrintNsClose_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_SectionKind.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsClose (FilePtr const & file, SectionKind skind, int depth);
}
#undef LZZ_INLINE
#endif
