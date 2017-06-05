// smtc_AcceptEntityVisitor.h
//

#ifndef LZZ_smtc_AcceptEntityVisitor_h
#define LZZ_smtc_AcceptEntityVisitor_h
// semantic
#include "smtc_EntityVisitor.h"
#include "smtc_EntityPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct AcceptEntityVisitor
  {
    EntityVisitor const & visitor;
    void operator () (EntityPtr const & entity);
  public:
    explicit AcceptEntityVisitor (EntityVisitor const & visitor);
    ~ AcceptEntityVisitor ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_AcceptEntityVisitor.inl"
#endif
#endif
