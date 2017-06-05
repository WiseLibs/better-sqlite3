// smtc_NsVisitor.cpp
//

#include "smtc_NsVisitor.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NsVisitor.inl"
#endif
// semantic
#include "smtc_LinkageNs.h"
#include "smtc_NamedNs.h"
#include "smtc_UnnamedNs.h"
#define LZZ_INLINE inline
namespace smtc
{
  void NsVisitor::visit (GlobalNs const & ns) const
    {}
}
namespace smtc
{
  void NsVisitor::visit (NestedNs const & ns) const
    {}
}
namespace smtc
{
  void NsVisitor::visit (NamedNs const & ns) const
    {
      visit (static_cast <NestedNs const &> (ns));
    }
}
namespace smtc
{
  void NsVisitor::visit (UnnamedNs const & ns) const
    {
      visit (static_cast <NestedNs const &> (ns));
    }
}
namespace smtc
{
  void NsVisitor::visit (LinkageNs const & ns) const
    {
      visit (static_cast <NestedNs const &> (ns));
    }
}
#undef LZZ_INLINE
