// smtc_AccessSpec.h
//

#ifndef LZZ_smtc_AccessSpec_h
#define LZZ_smtc_AccessSpec_h
// semantic
#include "smtc_Access.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  class AccessSpec
  {
    util::Loc m_loc;
    Access m_access;
  public:
    AccessSpec (util::Loc const & loc, Access access);
    ~ AccessSpec ();
    util::Loc const & getLoc () const;
    Access getAccess () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_AccessSpec.inl"
#endif
#endif
