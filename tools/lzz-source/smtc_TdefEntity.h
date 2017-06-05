// smtc_TdefEntity.h
//

#ifndef LZZ_smtc_TdefEntity_h
#define LZZ_smtc_TdefEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_TdefPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TdefEntity : public Entity
  {
    TdefPtr m_tdef;
  public:
    TdefEntity (TdefPtr const & tdef);
    ~ TdefEntity ();
    void accept (EntityVisitor const & visitor) const;
    TdefPtr const & getTdef () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TdefEntity.inl"
#endif
#endif
