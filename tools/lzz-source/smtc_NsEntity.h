// smtc_NsEntity.h
//

#ifndef LZZ_smtc_NsEntity_h
#define LZZ_smtc_NsEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NsEntity : public Entity
  {
    NsPtr m_ns;
  public:
    NsEntity (NsPtr const & ns);
    ~ NsEntity ();
    void accept (EntityVisitor const & visitor) const;
    NsPtr const & getNs () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NsEntity.inl"
#endif
#endif
