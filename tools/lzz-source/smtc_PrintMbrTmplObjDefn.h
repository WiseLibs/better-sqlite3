// smtc_PrintMbrTmplObjDefn.h
//

#ifndef LZZ_smtc_PrintMbrTmplObjDefn_h
#define LZZ_smtc_PrintMbrTmplObjDefn_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_ObjPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printMbrTmplObjDefn (Output & out, ObjPtr const & obj, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name);
}
#undef LZZ_INLINE
#endif
