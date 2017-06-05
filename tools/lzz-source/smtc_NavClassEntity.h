// smtc_NavClassEntity.h
//

#ifndef LZZ_smtc_NavClassEntity_h
#define LZZ_smtc_NavClassEntity_h
// semantic
#include "smtc_ClassDefnEntity.h"
#include "smtc_NavClassPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NavClassEntity : public ClassDefnEntity
  {
  public:
    NavClassEntity (NavClassPtr const & nav_class);
    ~ NavClassEntity ();
    void accept (EntityVisitor const & visitor) const;
    NavClassPtr getNavClass () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NavClassEntity.inl"
#endif
#endif
