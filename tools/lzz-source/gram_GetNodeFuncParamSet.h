// gram_GetNodeFuncParamSet.h
//

#ifndef LZZ_gram_GetNodeFuncParamSet_h
#define LZZ_gram_GetNodeFuncParamSet_h
// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_ParamPtrVector.h"
#define LZZ_INLINE inline
namespace gram
{
  void getNodeFuncParamSet (basl::Nonterm & nonterm, smtc::ParamPtrVector & param_set);
}
#undef LZZ_INLINE
#endif
