// smtc_PrintMbrDecl.h
//

#ifndef LZZ_smtc_PrintMbrDecl_h
#define LZZ_smtc_PrintMbrDecl_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrDecl (FilePtr const & file, ClassDefnPtr const & class_defn);
}
#undef LZZ_INLINE
#endif
