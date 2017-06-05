// smtc_PrintMbrClassDecl.h
//

#ifndef LZZ_smtc_PrintMbrClassDecl_h
#define LZZ_smtc_PrintMbrClassDecl_h
// semantic
#include "smtc_ClassDeclPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrClassDecl (FilePtr const & file, ClassDeclPtr const & class_decl);
}
#undef LZZ_INLINE
#endif
