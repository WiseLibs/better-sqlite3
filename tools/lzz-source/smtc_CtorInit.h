// smtc_CtorInit.h
//

#ifndef LZZ_smtc_CtorInit_h
#define LZZ_smtc_CtorInit_h
// semantic
#include "smtc_MbrInitPtrVector.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  class CtorInit
  {
    util::Loc m_loc;
    MbrInitPtrVector m_mbr_init_set;
  public:
    CtorInit (util::Loc const & loc, MbrInitPtrVector const & mbr_init_set);
    ~ CtorInit ();
    util::Loc const & getLoc () const;
    MbrInitPtrVector const & getMbrInitSet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_CtorInit.inl"
#endif
#endif
