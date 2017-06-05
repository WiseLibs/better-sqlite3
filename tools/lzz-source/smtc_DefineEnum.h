// smtc_DefineEnum.h
//

#ifndef LZZ_smtc_DefineEnum_h
#define LZZ_smtc_DefineEnum_h
// semantic
#include "smtc_EnumtorPtrVector.h"
#include "smtc_NamePtr.h"
#include "smtc_ScopePtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  void defineEnum (ScopePtr const & scope, util::Loc const & loc, NamePtr const & name, EnumtorPtrVector const & enumtor_set);
}
#undef LZZ_INLINE
#endif
