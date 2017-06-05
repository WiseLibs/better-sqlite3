// gram_GetNodeFuncParamBody.h
//

#ifndef LZZ_gram_GetNodeFuncParamBody_h
#define LZZ_gram_GetNodeFuncParamBody_h
// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_ParamPtrVector.h"
#define LZZ_INLINE inline
namespace gram
{
  void getNodeFuncParamBody (basl::Nonterm & nonterm, smtc::ParamPtrVector & param_set, bool & vararg);
}
#undef LZZ_INLINE
#endif
