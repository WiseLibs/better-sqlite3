// smtc_PrintEnum.h
//

#ifndef LZZ_smtc_PrintEnum_h
#define LZZ_smtc_PrintEnum_h
// semantic
#include "smtc_EnumPtr.h"
#include "smtc_FilePtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printEnum (FilePtr const & file, EnumPtr const & en, NsPtr const & ns);
}
namespace smtc
{
  void printEnum (FilePtr const & file, EnumPtr const & en);
}
#undef LZZ_INLINE
#endif
