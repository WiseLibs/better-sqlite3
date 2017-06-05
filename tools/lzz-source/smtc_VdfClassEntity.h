// smtc_VdfClassEntity.h
//

#ifndef LZZ_smtc_VdfClassEntity_h
#define LZZ_smtc_VdfClassEntity_h
// semantic
#include "smtc_ClassDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  class VdfClassEntity : public ClassDefnEntity
  {
  public:
    VdfClassEntity (ClassDefnPtr const & class_defn);
    ~ VdfClassEntity ();
    void accept (EntityVisitor const & visitor) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_VdfClassEntity.inl"
#endif
#endif
