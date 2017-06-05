// smtc_CreateClassDecl.cpp
//

#include "smtc_CreateClassDecl.h"
#include "smtc_ClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  ClassDeclPtr createClassDecl (ClassKey key, NamePtr const & name, bool is_dll_api)
  {
    return new ClassDecl (key, name, is_dll_api);
  }
}
#undef LZZ_INLINE
