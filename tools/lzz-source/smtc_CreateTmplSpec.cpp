// smtc_CreateTmplSpec.cpp
//

#include "smtc_CreateTmplSpec.h"
// semantic
#include "smtc_TmplSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplSpecPtr createTmplSpec (util::Loc const & loc, ParamPtrVector const & param_set)
  {
    return new TmplSpec (loc, param_set);
  }
}
#undef LZZ_INLINE
