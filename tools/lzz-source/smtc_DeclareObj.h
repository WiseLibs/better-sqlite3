// smtc_DeclareObj.h
//

#ifndef LZZ_smtc_DeclareObj_h
#define LZZ_smtc_DeclareObj_h
// semantic
#include "smtc_CvType.h"
#include "smtc_InitPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ScopePtr.h"

// gram
#include "gram_SpecSel.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareObj (ScopePtr const & scope, gram::SpecSel const & spec, CvType const & cv_type, NamePtr const & name, InitPtr const & init);
}
#undef LZZ_INLINE
#endif
