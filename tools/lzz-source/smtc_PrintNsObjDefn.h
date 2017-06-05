// smtc_PrintNsObjDefn.h
//

#ifndef LZZ_smtc_PrintNsObjDefn_h
#define LZZ_smtc_PrintNsObjDefn_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_ObjPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsObjDefn (Output & out, ObjPtr const & obj, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
