// smtc_PrintTmplSpecSet.h
//

#ifndef LZZ_smtc_PrintTmplSpecSet_h
#define LZZ_smtc_PrintTmplSpecSet_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_SectionKind.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printTmplSpecSet (FilePtr const & file, SectionKind skind, TmplSpecPtrVector const & tmpl_spec_set, bool is_decl);
}
#undef LZZ_INLINE
#endif
