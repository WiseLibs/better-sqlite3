// smtc_CheckSpecFlags.h
//

#ifndef LZZ_smtc_CheckSpecFlags_h
#define LZZ_smtc_CheckSpecFlags_h
// gram
#include "gram_SpecSel.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef void (* InvalidMsg) (util::Loc const &, char const *);
}
namespace smtc
{
  typedef void (* ConflictingMsg) (util::Loc const &, char const *, char const *);
}
namespace smtc
{
  void checkInvalidSpecFlags (gram::SpecSel const & spec_sel, int flags, InvalidMsg msg);
}
namespace smtc
{
  void checkValidSpecFlags (gram::SpecSel const & spec_sel, int flags, InvalidMsg msg);
}
namespace smtc
{
  void checkConflictingSpecFlags (gram::SpecSel const & spec_sel, int a_flags, int b_flags, ConflictingMsg msg);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_CheckSpecFlags.inl"
#endif
#endif
