// smtc_PrintNsEnum.h
//

#ifndef LZZ_smtc_PrintNsEnum_h
#define LZZ_smtc_PrintNsEnum_h
// semantic
#include "smtc_EnumPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsEnum (Output & out, EnumPtr const & en, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
