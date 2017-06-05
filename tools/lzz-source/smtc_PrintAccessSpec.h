// smtc_PrintAccessSpec.h
//

#ifndef LZZ_smtc_PrintAccessSpec_h
#define LZZ_smtc_PrintAccessSpec_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_AccessSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printAccessSpec (FilePtr const & file, AccessSpecPtr const & access_spec);
}
#undef LZZ_INLINE
#endif
