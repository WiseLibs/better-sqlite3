// smtc_CreateEnum.cpp
//

#include "smtc_CreateEnum.h"
// semantic
#include "smtc_Enum.h"
#define LZZ_INLINE inline
namespace smtc
{
  EnumPtr createEnum (util::Loc const & loc, NamePtr const & name, EnumtorPtrVector const & enumtor_set)
  {
    return new Enum (loc, name, enumtor_set);
  }
}
#undef LZZ_INLINE
