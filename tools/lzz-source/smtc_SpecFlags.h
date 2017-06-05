// smtc_SpecFlags.h
//

#ifndef LZZ_smtc_SpecFlags_h
#define LZZ_smtc_SpecFlags_h
// gram
#include "gram_DclSpecFlags.h"
#define LZZ_INLINE inline
namespace smtc
{
  enum
  {
    INLINE_SPEC = gram::INLINE_SPEC,
    VIRTUAL_SPEC = gram::VIRTUAL_SPEC,
    EXPLICIT_SPEC = gram::EXPLICIT_SPEC,
    STATIC_SPEC = gram::STATIC_SPEC,
    EXTERN_SPEC = gram::EXTERN_SPEC,
    MUTABLE_SPEC = gram::MUTABLE_SPEC,
    AUTO_SPEC = gram::AUTO_SPEC,
    REGISTER_SPEC = gram::REGISTER_SPEC,
    PURE_SPEC = gram::PURE_SPEC,
    DLL_API_SPEC = gram::DLL_API_SPEC
  };
}
#undef LZZ_INLINE
#endif
