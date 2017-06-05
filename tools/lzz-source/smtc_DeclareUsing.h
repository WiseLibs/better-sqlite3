// smtc_DeclareUsing.h
//

#ifndef LZZ_smtc_DeclareUsing_h
#define LZZ_smtc_DeclareUsing_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareUsing (ScopePtr const & scope, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
