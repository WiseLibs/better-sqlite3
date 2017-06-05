// smtc_PrintTmplClassDecl.h
//

#ifndef LZZ_smtc_PrintTmplClassDecl_h
#define LZZ_smtc_PrintTmplClassDecl_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_PrintClassDecl.h"
#include "smtc_TmplClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintTmplClassDecl : PrintClassDecl
  {
    void print (FilePtr const & file, TmplClassDeclPtr const & tmpl_class_decl, NsPtr const & ns) const;
    void print (FilePtr const & file, TmplClassDeclPtr const & tmpl_class_decl) const;
  };
}
#undef LZZ_INLINE
#endif
