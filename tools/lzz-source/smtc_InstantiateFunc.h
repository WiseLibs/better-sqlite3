// smtc_InstantiateFunc.h
//

#ifndef LZZ_smtc_InstantiateFunc_h
#define LZZ_smtc_InstantiateFunc_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"
#include "smtc_ThrowSpecPtr.h"

// gram
#include "gram_SpecSel.h"
#define LZZ_INLINE inline
namespace smtc
{
  void instantiateFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
