// smtc_CreateTmplClassDecl.cpp
//

#include "smtc_CreateTmplClassDecl.h"
#include "smtc_CreateClassDecl.h"
#include "smtc_TmplClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplClassDeclPtr createTmplClassDecl (TmplSpecPtrVector const & tmpl_spec_set, ClassKey key, NamePtr const & name)
  {
    bool is_dll_api = false;
    ClassDeclPtr class_decl = createClassDecl (key, name, is_dll_api);
    return new TmplClassDecl (tmpl_spec_set, class_decl);
  }
}
#undef LZZ_INLINE
