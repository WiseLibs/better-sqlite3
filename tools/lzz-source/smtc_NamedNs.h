// smtc_NamedNs.h
//

#ifndef LZZ_smtc_NamedNs_h
#define LZZ_smtc_NamedNs_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_NestedNs.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NamedNs : public NestedNs
  {
    NamePtr m_name;
  public:
    NamedNs (NsPtr const & encl_ns, util::Loc const & loc, NamePtr const & name);
    ~ NamedNs ();
    void accept (NsVisitor const & visitor) const;
    NamePtr const & getName () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NamedNs.inl"
#endif
#endif
