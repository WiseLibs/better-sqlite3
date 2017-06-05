// gram_MacroArgPtr.h
//

#ifndef LZZ_gram_MacroArgPtr_h
#define LZZ_gram_MacroArgPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace gram
{
  class MacroArg;
}
namespace gram
{
  typedef util::BPtr <MacroArg> MacroArgPtr;
}
#undef LZZ_INLINE
#endif
