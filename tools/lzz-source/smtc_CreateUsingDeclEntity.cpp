// smtc_CreateUsingDeclEntity.cpp
//

#include "smtc_CreateUsingDeclEntity.h"
// semantic
#include "smtc_UsingDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createUsingDeclEntity (UsingDeclPtr const & using_decl)
  {
    return new UsingDeclEntity (using_decl);
  }
}
#undef LZZ_INLINE
