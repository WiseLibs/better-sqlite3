// smtc_DeclareFunc.h
//

#ifndef LZZ_smtc_DeclareFunc_h
#define LZZ_smtc_DeclareFunc_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"
#include "smtc_ThrowSpecPtr.h"
#include "smtc_TmplSpecPtrVector.h"

// gram
#include "gram_SpecSel.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
}
namespace smtc
{
  void declareFrndFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
}
#undef LZZ_INLINE
#endif
