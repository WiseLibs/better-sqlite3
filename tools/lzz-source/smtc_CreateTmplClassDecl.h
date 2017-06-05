// smtc_CreateTmplClassDecl.h
//

#ifndef LZZ_smtc_CreateTmplClassDecl_h
#define LZZ_smtc_CreateTmplClassDecl_h
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#include "smtc_TmplClassDeclPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplClassDeclPtr createTmplClassDecl (TmplSpecPtrVector const & tmpl_spec_set, ClassKey key, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
