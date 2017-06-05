// smtc_DefineNavVisitFunc.h
//

#ifndef LZZ_smtc_DefineNavVisitFunc_h
#define LZZ_smtc_DefineNavVisitFunc_h
// semantic
#include "smtc_ScopePtr.h"
#include "smtc_NamePtr.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  void defineNavVisitFunc (ScopePtr const & cs, NamePtr const & type_name, NamePtr const & param_name, gram::Block const & body);
}
#undef LZZ_INLINE
#endif
