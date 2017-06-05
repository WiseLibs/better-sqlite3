// smtc_CreateClassDecl.h
//

#ifndef LZZ_smtc_CreateClassDecl_h
#define LZZ_smtc_CreateClassDecl_h
#include "smtc_ClassDeclPtr.h"
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ClassDeclPtr createClassDecl (ClassKey key, NamePtr const & name, bool is_dll_api);
}
#undef LZZ_INLINE
#endif
