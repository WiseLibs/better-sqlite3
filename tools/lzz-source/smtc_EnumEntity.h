// smtc_EnumEntity.h
//

#ifndef LZZ_smtc_EnumEntity_h
#define LZZ_smtc_EnumEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_EnumPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class EnumEntity : public Entity
  {
    EnumPtr m_en;
  public:
    EnumEntity (EnumPtr const & en);
    ~ EnumEntity ();
    void accept (EntityVisitor const & visitor) const;
    EnumPtr const & getEnum () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_EnumEntity.inl"
#endif
#endif
