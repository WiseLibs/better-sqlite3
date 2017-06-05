// smtc_PrintMbrFrndTmplClassDecl.h
//

#ifndef LZZ_smtc_PrintMbrFrndTmplClassDecl_h
#define LZZ_smtc_PrintMbrFrndTmplClassDecl_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_TmplClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndTmplClassDecl (FilePtr const & file, TmplClassDeclPtr const & tmpl_class_decl);
}
#undef LZZ_INLINE
#endif
