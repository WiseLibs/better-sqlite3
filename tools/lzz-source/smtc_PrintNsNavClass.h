// smtc_PrintNsNavClass.h
//

#ifndef LZZ_smtc_PrintNsNavClass_h
#define LZZ_smtc_PrintNsNavClass_h
// semantic
#include "smtc_NavClassPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsNavClass (Output & out, NavClassPtr const & nav_class, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
