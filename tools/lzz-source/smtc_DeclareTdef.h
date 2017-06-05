// smtc_DeclareTdef.h
//

#ifndef LZZ_smtc_DeclareTdef_h
#define LZZ_smtc_DeclareTdef_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareTdef (ScopePtr const & scope, CvType const & cv_type, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
