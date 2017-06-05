// smtc_PrintMbrObjDefn.h
//

#ifndef LZZ_smtc_PrintMbrObjDefn_h
#define LZZ_smtc_PrintMbrObjDefn_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_ObjPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printMbrObjDefn (Output & out, ObjPtr const & obj, NsPtr const & ns, NamePtr const & qual_name);
}
#undef LZZ_INLINE
#endif
