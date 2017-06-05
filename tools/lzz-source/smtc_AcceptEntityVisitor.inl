// smtc_AcceptEntityVisitor.inl
//

// semantic
#include "smtc_Entity.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE void AcceptEntityVisitor::operator () (EntityPtr const & entity)
  {
    entity->accept (visitor);
  }
}
namespace smtc
{
  LZZ_INLINE AcceptEntityVisitor::AcceptEntityVisitor (EntityVisitor const & visitor)
    : visitor (visitor)
              {}
}
#undef LZZ_INLINE
