// smtc_PrintMbrTmplClassDecl.h
//

#ifndef LZZ_smtc_PrintMbrTmplClassDecl_h
#define LZZ_smtc_PrintMbrTmplClassDecl_h
// semantic
#include "smtc_TmplClassDeclPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplClassDecl (FilePtr const & file, TmplClassDeclPtr const & tmpl_class_decl);
}
#undef LZZ_INLINE
#endif
