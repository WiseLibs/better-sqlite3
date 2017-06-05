// smtc_CreateEnum.h
//

#ifndef LZZ_smtc_CreateEnum_h
#define LZZ_smtc_CreateEnum_h
// semantic
#include "smtc_EnumPtr.h"
#include "smtc_EnumtorPtrVector.h"
#include "smtc_NamePtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  EnumPtr createEnum (util::Loc const & loc, NamePtr const & name, EnumtorPtrVector const & enumtor_set);
}
#undef LZZ_INLINE
#endif
