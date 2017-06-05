// smtc_DeclareClass.h
//

#ifndef LZZ_smtc_DeclareClass_h
#define LZZ_smtc_DeclareClass_h
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareClass (ScopePtr const & scope, ClassKey key, NamePtr const & name, bool is_dll_api);
}
namespace smtc
{
  void declareFrndClass (ScopePtr const & scope, ClassKey key, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
