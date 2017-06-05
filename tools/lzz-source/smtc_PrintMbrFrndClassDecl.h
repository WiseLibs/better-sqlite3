// smtc_PrintMbrFrndClassDecl.h
//

#ifndef LZZ_smtc_PrintMbrFrndClassDecl_h
#define LZZ_smtc_PrintMbrFrndClassDecl_h
// semantic
#include "smtc_ClassDeclPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrFrndClassDecl (FilePtr const & file, ClassDeclPtr const & class_decl);
}
#undef LZZ_INLINE
#endif
