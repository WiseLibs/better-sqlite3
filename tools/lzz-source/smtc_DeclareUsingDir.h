// smtc_DeclareUsingDir.h
//

#ifndef LZZ_smtc_DeclareUsingDir_h
#define LZZ_smtc_DeclareUsingDir_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareUsingDir (ScopePtr const & scope, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
