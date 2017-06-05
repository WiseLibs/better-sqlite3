// smtc_ScopeVisitor.cpp
//

#include "smtc_ScopeVisitor.h"
// semantic
#include "smtc_LazyClassScope.h"
#include "smtc_NavClassScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  void ScopeVisitor::visit (NsScope const & scope) const
    {}
}
namespace smtc
{
  void ScopeVisitor::visit (ClassScope const & scope) const
    {}
}
namespace smtc
{
  void ScopeVisitor::visit (TmplSpecScope const & scope) const
    {}
}
namespace smtc
{
  void ScopeVisitor::visit (TmplInstScope const & scope) const
    {}
}
namespace smtc
{
  void ScopeVisitor::visit (LazyClassScope const & scope) const
    {
      visit (static_cast <ClassScope const &> (scope));
    }
}
namespace smtc
{
  void ScopeVisitor::visit (LinkageSpecScope const & scope) const
    {}
}
namespace smtc
{
  void ScopeVisitor::visit (NavClassScope const & scope) const
    {
      visit (static_cast <ClassScope const &> (scope));
    }
}
namespace smtc
{
  void ScopeVisitor::visit (VdfScope const & scope) const
    {}
}
namespace smtc
{
  void ScopeVisitor::visit (VdfBlockDataScope const & scope) const
    {}
}
#undef LZZ_INLINE
