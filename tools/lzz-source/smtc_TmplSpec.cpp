// smtc_TmplSpec.cpp
//

#include "smtc_TmplSpec.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplSpec.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  TmplSpec::TmplSpec (util::Loc const & loc, ParamPtrVector const & param_set)
    : m_loc (loc), m_param_set (param_set)
    {}
}
namespace smtc
{
  TmplSpec::~ TmplSpec ()
    {}
}
#undef LZZ_INLINE
