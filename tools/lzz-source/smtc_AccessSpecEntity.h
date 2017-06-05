// smtc_AccessSpecEntity.h
//

#ifndef LZZ_smtc_AccessSpecEntity_h
#define LZZ_smtc_AccessSpecEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_AccessSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class AccessSpecEntity : public Entity
  {
    AccessSpecPtr m_access_spec;
  public:
    AccessSpecEntity (AccessSpecPtr const & access_spec);
    ~ AccessSpecEntity ();
    void accept (EntityVisitor const & visitor) const;
    AccessSpecPtr const & getAccessSpec () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_AccessSpecEntity.inl"
#endif
#endif
