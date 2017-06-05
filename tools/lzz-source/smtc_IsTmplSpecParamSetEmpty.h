// smtc_IsTmplSpecParamSetEmpty.h
//

#ifndef LZZ_smtc_IsTmplSpecParamSetEmpty_h
#define LZZ_smtc_IsTmplSpecParamSetEmpty_h
// std lib
#include <functional>

// semantic
#include "smtc_TmplSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct IsTmplSpecParamSetEmpty : std::unary_function <TmplSpecPtr, bool>
  {
    bool operator () (TmplSpecPtr const & tmpl_spec) const;
  public:
    explicit IsTmplSpecParamSetEmpty ();
    ~ IsTmplSpecParamSetEmpty ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_IsTmplSpecParamSetEmpty.inl"
#endif
#endif
