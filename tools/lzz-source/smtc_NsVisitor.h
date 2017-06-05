// smtc_NsVisitor.h
//

#ifndef LZZ_smtc_NsVisitor_h
#define LZZ_smtc_NsVisitor_h
#define LZZ_INLINE inline
namespace smtc
{
  class GlobalNs;
}
namespace smtc
{
  class LinkageNs;
}
namespace smtc
{
  class NamedNs;
}
namespace smtc
{
  class NestedNs;
}
namespace smtc
{
  class UnnamedNs;
}
namespace smtc
{
  struct NsVisitor
  {
    NsVisitor ();
    ~ NsVisitor ();
    virtual void visit (GlobalNs const & ns) const;
    virtual void visit (NestedNs const & ns) const;
    virtual void visit (NamedNs const & ns) const;
    virtual void visit (UnnamedNs const & ns) const;
    virtual void visit (LinkageNs const & ns) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NsVisitor.inl"
#endif
#endif
