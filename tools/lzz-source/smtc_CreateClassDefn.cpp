// smtc_CreateClassDefn.cpp
//

#include "smtc_CreateClassDefn.h"
#include "smtc_ClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  ClassDefnPtr createClassDefn (ClassKey key, NamePtr const & name, bool is_dll_api, BaseSpecPtrVector const & base_spec_set)
  {
    return new ClassDefn (key, name, is_dll_api, base_spec_set);
  }
}
#undef LZZ_INLINE
