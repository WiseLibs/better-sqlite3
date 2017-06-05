// smtc_CreateClassScope.h
//

#ifndef LZZ_smtc_CreateClassScope_h
#define LZZ_smtc_CreateClassScope_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createClassScope (ClassDefnPtr const & class_defn);
}
#undef LZZ_INLINE
#endif
