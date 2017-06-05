// smtc_PrintNs.h
//

#ifndef LZZ_smtc_PrintNs_h
#define LZZ_smtc_PrintNs_h
// semantic
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNs (Output & out, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
