// smtc_CheckSpecFlags.cpp
//

#include "smtc_CheckSpecFlags.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_CheckSpecFlags.inl"
#endif
// semantic
#include "smtc_SpecToString.h"
#define LZZ_INLINE inline
namespace smtc
{
  void checkInvalidSpecFlags (gram::SpecSel const & spec_sel, int flags, InvalidMsg msg)
  {
    flags &= spec_sel.getFlags ();
    for (int i = 1; i <= flags; i <<= 1)
    {
      if (i & flags)
      {
        msg (spec_sel.getSpecLoc (i), specToString (i));
      }
    }
  }
}
namespace smtc
{
  void checkConflictingSpecFlags (gram::SpecSel const & spec_sel, int a_flags, int b_flags, ConflictingMsg msg)
  {
    int flags = spec_sel.getFlags ();
    a_flags &= flags;
    b_flags &= flags;
    for (int i = 1; i <= a_flags; i <<= 1)
    {
      if (i & a_flags)
      {
        for (int j = i << 1; j <= a_flags; j <<= 1)
        {
          if (j & a_flags)
          {
            msg (spec_sel.getSpecLoc (j), specToString (j), specToString (i));
            a_flags &= ~ j;
          }
        }
        for (int k = 1; k <= b_flags; k <<= 1)
        {
          if (k & b_flags)
          {
            msg (spec_sel.getSpecLoc (k), specToString (k), specToString (i));
          }
        }
      }
    }
  }
}
#undef LZZ_INLINE
