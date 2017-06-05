// smtc_CreateClassScope.cpp
//

#include "smtc_CreateClassScope.h"
// semantic
#include "smtc_ClassScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createClassScope (ClassDefnPtr const & class_defn)
  {
    return new ClassScope (class_defn);
  }
}
#undef LZZ_INLINE
