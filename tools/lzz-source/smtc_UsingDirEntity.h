// smtc_UsingDirEntity.h
//

#ifndef LZZ_smtc_UsingDirEntity_h
#define LZZ_smtc_UsingDirEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_UsingDirPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UsingDirEntity : public Entity
  {
    UsingDirPtr m_using_dir;
  public:
    UsingDirEntity (UsingDirPtr const & using_dir);
    ~ UsingDirEntity ();
    void accept (EntityVisitor const & visitor) const;
    UsingDirPtr const & getUsingDir () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_UsingDirEntity.inl"
#endif
#endif
