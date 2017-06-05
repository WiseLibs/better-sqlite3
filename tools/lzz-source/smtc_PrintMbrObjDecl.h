// smtc_PrintMbrObjDecl.h
//

#ifndef LZZ_smtc_PrintMbrObjDecl_h
#define LZZ_smtc_PrintMbrObjDecl_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_ObjPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrObjDecl (FilePtr const & file, ObjPtr const & obj);
}
#undef LZZ_INLINE
#endif
