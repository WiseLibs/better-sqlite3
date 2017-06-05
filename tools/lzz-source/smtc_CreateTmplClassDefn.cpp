// smtc_CreateTmplClassDefn.cpp
//

#include "smtc_CreateTmplClassDefn.h"
#include "smtc_CreateClassDefn.h"
#include "smtc_TmplClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplClassDefnPtr createTmplClassDefn (TmplSpecPtrVector const & tmpl_spec_set, ClassKey key, NamePtr const & name, BaseSpecPtrVector const & base_spec_set)
  {
    bool is_dll_api = false;
    ClassDefnPtr class_defn = createClassDefn (key, name, is_dll_api, base_spec_set);
    return new TmplClassDefn (tmpl_spec_set, class_defn);
  }
}
namespace smtc
{
  TmplClassDefnPtr createTmplClassDefn (TmplSpecPtrVector const & tmpl_spec_set, ClassDefnPtr const & class_defn)
  {
    return new TmplClassDefn (tmpl_spec_set, class_defn);
  }
}
#undef LZZ_INLINE
