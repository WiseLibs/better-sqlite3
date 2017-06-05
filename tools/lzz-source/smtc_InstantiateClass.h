// smtc_InstantiateClass.h
//

#ifndef LZZ_smtc_InstantiateClass_h
#define LZZ_smtc_InstantiateClass_h
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void instantiateClass (ScopePtr const & scope, ClassKey key, NamePtr const & name, bool is_dll_api);
}
#undef LZZ_INLINE
#endif
