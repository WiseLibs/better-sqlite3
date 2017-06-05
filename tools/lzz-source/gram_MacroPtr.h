// gram_MacroPtr.h
//

#ifndef LZZ_gram_MacroPtr_h
#define LZZ_gram_MacroPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace gram
{
  class Macro;
}
namespace gram
{
  typedef util::BPtr <Macro> MacroPtr;
}
#undef LZZ_INLINE
#endif
