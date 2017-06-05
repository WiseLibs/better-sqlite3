// smtc_CreateAccessSpecEntity.h
//

#ifndef LZZ_smtc_CreateAccessSpecEntity_h
#define LZZ_smtc_CreateAccessSpecEntity_h
// semantic
#include "smtc_AccessSpecPtr.h"
#include "smtc_EntityPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createAccessSpecEntity (AccessSpecPtr const & access_spec);
}
#undef LZZ_INLINE
#endif
