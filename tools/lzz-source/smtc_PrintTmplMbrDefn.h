// smtc_PrintTmplMbrDefn.h
//

#ifndef LZZ_smtc_PrintTmplMbrDefn_h
#define LZZ_smtc_PrintTmplMbrDefn_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_TmplClassDefnPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  void printTmplMbrDefn (Output & out, TmplClassDefnPtr const & tmpl_class_defn, NsPtr const & ns);
}
namespace smtc
{
  void printTmplMbrDefn (Output & out, TmplClassDefnPtr const & tmpl_class_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns);
}
namespace smtc
{
  void printTmplMbrDefn (Output & out, ClassDefnPtr const & class_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
