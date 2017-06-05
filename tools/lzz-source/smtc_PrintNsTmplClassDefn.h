// smtc_PrintNsTmplClassDefn.h
//

#ifndef LZZ_smtc_PrintNsTmplClassDefn_h
#define LZZ_smtc_PrintNsTmplClassDefn_h
// semantic
#include "smtc_TmplClassDefnPtr.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printNsTmplClassDefn (Output & out, TmplClassDefnPtr const & tmpl_class_defn, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
