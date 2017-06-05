// smtc_PrintMbrUsingDecl.h
//

#ifndef LZZ_smtc_PrintMbrUsingDecl_h
#define LZZ_smtc_PrintMbrUsingDecl_h
// semantic
#include "smtc_UsingDeclPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrUsingDecl (FilePtr const & file, UsingDeclPtr const & using_decl);
}
#undef LZZ_INLINE
#endif
