// smtc_CreateClassDefn.h
//

#ifndef LZZ_smtc_CreateClassDefn_h
#define LZZ_smtc_CreateClassDefn_h
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_ClassDefnPtr.h"
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ClassDefnPtr createClassDefn (ClassKey key, NamePtr const & name, bool is_dll_api, BaseSpecPtrVector const & base_spec_set);
}
#undef LZZ_INLINE
#endif
