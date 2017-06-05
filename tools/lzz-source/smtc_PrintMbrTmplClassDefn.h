// smtc_PrintMbrTmplClassDefn.h
//

#ifndef LZZ_smtc_PrintMbrTmplClassDefn_h
#define LZZ_smtc_PrintMbrTmplClassDefn_h
// semantic
#include "smtc_TmplClassDefnPtr.h"
#include "smtc_FilePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplClassDefn (FilePtr const & file, TmplClassDefnPtr const & tmpl_class_defn);
}
#undef LZZ_INLINE
#endif
