// smtc_DefineFunc.h
//

#ifndef LZZ_smtc_DefineFunc_h
#define LZZ_smtc_DefineFunc_h
// semantic
#include "smtc_CtorInitPtr.h"
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"
#include "smtc_ThrowSpecPtr.h"
#include "smtc_TryBlockPtr.h"

// gram
#include "gram_SpecSel.h"
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  void defineFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block);
}
namespace smtc
{
  void defineFrndFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block);
}
#undef LZZ_INLINE
#endif
