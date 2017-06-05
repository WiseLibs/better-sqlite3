// smtc_NestedNs.h
//

#ifndef LZZ_smtc_NestedNs_h
#define LZZ_smtc_NestedNs_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_Ns.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct NsVisitor;
}
namespace smtc
{
  class NestedNs : public Ns
  {
    NsPtr m_encl_ns;
    util::Loc m_loc;
  public:
    NestedNs (NsPtr const & encl_ns, util::Loc const & loc);
    ~ NestedNs ();
    NsPtr const & getEnclNs () const;
    util::Loc const & getLoc () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NestedNs.inl"
#endif
#endif
