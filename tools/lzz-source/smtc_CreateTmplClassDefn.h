// smtc_CreateTmplClassDefn.h
//

#ifndef LZZ_smtc_CreateTmplClassDefn_h
#define LZZ_smtc_CreateTmplClassDefn_h
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_ClassDefnPtr.h"
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#include "smtc_TmplClassDefnPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplClassDefnPtr createTmplClassDefn (TmplSpecPtrVector const & tmpl_spec_set, ClassKey key, NamePtr const & name, BaseSpecPtrVector const & base_spec_set);
}
namespace smtc
{
  TmplClassDefnPtr createTmplClassDefn (TmplSpecPtrVector const & tmpl_spec_set, ClassDefnPtr const & class_defn);
}
#undef LZZ_INLINE
#endif
