// basl_RecCmdPtr.h
//

#ifndef LZZ_basl_RecCmdPtr_h
#define LZZ_basl_RecCmdPtr_h
// basil
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace basl
{
  class RecCmd;
}
namespace basl
{
  typedef util::BPtr <RecCmd> RecCmdPtr;
}
#undef LZZ_INLINE
#endif
