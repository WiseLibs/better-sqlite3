// smtc_DefineVdfShortData.h
//

#ifndef LZZ_smtc_DefineVdfShortData_h
#define LZZ_smtc_DefineVdfShortData_h
// semantic
#include "smtc_CvType.h"
#include "smtc_InitPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#include "util_String.h"

#define LZZ_INLINE inline
namespace smtc
{
  void defineVdfShortData (ScopePtr const & scope, CvType const & type, util::Loc const & loc, util::Ident const & ident, ParamPtrVector const & param_set, bool vararg, InitPtr const & init);
}
namespace smtc
{
  void defineVdfShortData (ScopePtr const & scope, CvType const & type, util::Loc const & loc, util::String const & str, ParamPtrVector const & param_set, bool vararg, InitPtr const & init);
}
#undef LZZ_INLINE
#endif
