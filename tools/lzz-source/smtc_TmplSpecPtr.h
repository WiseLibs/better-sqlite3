// smtc_TmplSpecPtr.h
//

#ifndef LZZ_smtc_TmplSpecPtr_h
#define LZZ_smtc_TmplSpecPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplSpec;
}
namespace smtc
{
  typedef util::BPtr <TmplSpec> TmplSpecPtr;
}
#undef LZZ_INLINE
#endif
