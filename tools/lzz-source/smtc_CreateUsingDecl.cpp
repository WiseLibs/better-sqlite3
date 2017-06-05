// smtc_CreateUsingDecl.cpp
//

#include "smtc_CreateUsingDecl.h"
// semantic
#include "smtc_UsingDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  UsingDeclPtr createUsingDecl (NamePtr const & name)
  {
    return new UsingDecl (name);
  }
}
#undef LZZ_INLINE
