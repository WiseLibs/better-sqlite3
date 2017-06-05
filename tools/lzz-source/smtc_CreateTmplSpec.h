// smtc_CreateTmplSpec.h
//

#ifndef LZZ_smtc_CreateTmplSpec_h
#define LZZ_smtc_CreateTmplSpec_h
// semantic
#include "smtc_ParamPtrVector.h"
#include "smtc_TmplSpecPtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplSpecPtr createTmplSpec (util::Loc const & loc, ParamPtrVector const & param_set);
}
#undef LZZ_INLINE
#endif
