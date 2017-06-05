// basl_AttribPtr.h
//

#ifndef LZZ_basl_AttribPtr_h
#define LZZ_basl_AttribPtr_h
// util
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace basl
{
  class Attrib;
}
namespace basl
{
  typedef util::BPtr <Attrib> AttribPtr;
}
#undef LZZ_INLINE
#endif
