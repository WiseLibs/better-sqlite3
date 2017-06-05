// smtc_PrintNsTdef.h
//

#ifndef LZZ_smtc_PrintNsTdef_h
#define LZZ_smtc_PrintNsTdef_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_TdefPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsTdef (Output & out, TdefPtr const & tdef, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
