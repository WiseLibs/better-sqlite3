// basl_RecCmdPtrDeque.h
//

#ifndef LZZ_basl_RecCmdPtrDeque_h
#define LZZ_basl_RecCmdPtrDeque_h
// std lib
#include <deque>

// basl
#include "basl_RecCmdPtr.h"
#define LZZ_INLINE inline
namespace basl
{
  typedef std::deque <RecCmdPtr> RecCmdPtrDeque;
}
namespace basl
{
  typedef std::deque <RecCmdPtr>::const_iterator RecCmdPtrDequeConstIter;
}
#undef LZZ_INLINE
#endif
