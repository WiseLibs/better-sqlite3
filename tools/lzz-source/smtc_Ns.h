// smtc_Ns.h
//

#ifndef LZZ_smtc_Ns_h
#define LZZ_smtc_Ns_h
// semantic
#include "smtc_EntityPtrDeque.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct NsVisitor;
}
namespace smtc
{
  class Ns
  {
    EntityPtrDeque m_entity_set;
  public:
    Ns ();
    virtual ~ Ns ();
    virtual void accept (NsVisitor const & visitor) const = 0;
    void addEntity (EntityPtr const & entity);
    EntityPtrDeque const & getEntitySet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Ns.inl"
#endif
#endif
