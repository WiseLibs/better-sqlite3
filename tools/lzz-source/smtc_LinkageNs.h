// smtc_LinkageNs.h
//

#ifndef LZZ_smtc_LinkageNs_h
#define LZZ_smtc_LinkageNs_h
// semantic
#include "smtc_NestedNs.h"
// util
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  class LinkageNs : public NestedNs
  {
    util::Ident m_linkage;
  public:
    LinkageNs (NsPtr const & encl_ns, util::Loc const & loc, util::Ident const & linkage);
    ~ LinkageNs ();
    void accept (NsVisitor const & visitor) const;
    util::Ident const & getLinkage () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_LinkageNs.inl"
#endif
#endif
