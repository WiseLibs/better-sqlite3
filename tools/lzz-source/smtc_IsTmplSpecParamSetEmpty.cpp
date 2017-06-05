// smtc_IsTmplSpecParamSetEmpty.cpp
//

#include "smtc_IsTmplSpecParamSetEmpty.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_IsTmplSpecParamSetEmpty.inl"
#endif
// semantic
#include "smtc_TmplSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool IsTmplSpecParamSetEmpty::operator () (TmplSpecPtr const & tmpl_spec) const
  {
    return tmpl_spec->getParamSet ().empty ();
  }
}
namespace smtc
{
  IsTmplSpecParamSetEmpty::~ IsTmplSpecParamSetEmpty ()
       {}
}
#undef LZZ_INLINE
