// smtc_UnnamedNs.h
//

#ifndef LZZ_smtc_UnnamedNs_h
#define LZZ_smtc_UnnamedNs_h
// semantic
#include "smtc_NestedNs.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UnnamedNs : public NestedNs
  {
  public:
    UnnamedNs (NsPtr const & encl_ns, util::Loc const & loc);
    ~ UnnamedNs ();
    void accept (NsVisitor const & visitor) const;
  };
}
#undef LZZ_INLINE
#endif
