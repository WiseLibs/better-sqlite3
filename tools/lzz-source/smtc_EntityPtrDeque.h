// smtc_EntityPtrDeque.h
//

#ifndef LZZ_smtc_EntityPtrDeque_h
#define LZZ_smtc_EntityPtrDeque_h
// std lib
#include <deque>

// semantic
#include "smtc_EntityPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::deque <EntityPtr> EntityPtrDeque;
}
namespace smtc
{
  typedef std::deque <EntityPtr>::iterator EntityPtrDequeIter;
}
namespace smtc
{
  typedef std::deque <EntityPtr>::const_iterator EntityPtrDequeConstIter;
}
namespace smtc
{
  typedef std::deque <EntityPtr>::reverse_iterator EntityPtrDequeRevIter;
}
namespace smtc
{
  typedef std::deque <EntityPtr>::const_reverse_iterator EntityPtrDequeConstRevIter;
}
#undef LZZ_INLINE
#endif
