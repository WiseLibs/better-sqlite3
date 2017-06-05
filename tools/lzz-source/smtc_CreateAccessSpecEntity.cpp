// smtc_CreateAccessSpecEntity.cpp
//

#include "smtc_CreateAccessSpecEntity.h"
// semantic
#include "smtc_AccessSpecEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createAccessSpecEntity (AccessSpecPtr const & access_spec)
  {
    return new AccessSpecEntity (access_spec);
  }
}
#undef LZZ_INLINE
