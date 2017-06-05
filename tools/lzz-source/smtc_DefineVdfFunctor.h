// smtc_DefineVdfFunctor.h
//

#ifndef LZZ_smtc_DefineVdfFunctor_h
#define LZZ_smtc_DefineVdfFunctor_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"
#include "smtc_TryBlockPtr.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  void defineVdfFunctor (ScopePtr const & scope, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, gram::Block const & body, TryBlockPtr const & try_block);
}
#undef LZZ_INLINE
#endif
