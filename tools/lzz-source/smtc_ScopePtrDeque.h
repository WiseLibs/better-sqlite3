// smtc_ScopePtrDeque.h
//

#ifndef LZZ_smtc_ScopePtrDeque_h
#define LZZ_smtc_ScopePtrDeque_h
// std lib
#include <deque>

// semantic
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::deque <ScopePtr> ScopePtrDeque;
}
namespace smtc
{
  typedef std::deque <ScopePtr>::iterator ScopePtrDequeIter;
}
namespace smtc
{
  typedef std::deque <ScopePtr>::const_iterator ScopePtrDequeConstIter;
}
namespace smtc
{
  typedef std::deque <ScopePtr>::reverse_iterator ScopePtrDequeRevIter;
}
namespace smtc
{
  typedef std::deque <ScopePtr>::const_reverse_iterator ScopePtrDequeConstRevIter;
}
#undef LZZ_INLINE
#endif
