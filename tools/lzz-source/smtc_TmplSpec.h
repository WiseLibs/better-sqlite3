// smtc_TmplSpec.h
//

#ifndef LZZ_smtc_TmplSpec_h
#define LZZ_smtc_TmplSpec_h
// semantic
#include "smtc_ParamPtrVector.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplSpec
  {
    util::Loc m_loc;
    ParamPtrVector m_param_set;
  public:
    TmplSpec (util::Loc const & loc, ParamPtrVector const & param_set);
    ~ TmplSpec ();
    util::Loc const & getLoc () const;
    ParamPtrVector const & getParamSet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplSpec.inl"
#endif
#endif
