// smtc_Entity.h
//

#ifndef LZZ_smtc_Entity_h
#define LZZ_smtc_Entity_h
#define LZZ_INLINE inline
namespace smtc
{
  struct EntityVisitor;
}
namespace smtc
{
  class Entity
  {
  public:
    Entity ();
    virtual ~ Entity ();
    virtual void accept (EntityVisitor const & visitor) const = 0;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Entity.inl"
#endif
#endif
