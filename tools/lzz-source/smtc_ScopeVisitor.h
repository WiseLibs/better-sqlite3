// smtc_ScopeVisitor.h
//

#ifndef LZZ_smtc_ScopeVisitor_h
#define LZZ_smtc_ScopeVisitor_h
#define LZZ_INLINE inline
namespace smtc
{
  class NsScope;
}
namespace smtc
{
  class ClassScope;
}
namespace smtc
{
  class VdfScope;
}
namespace smtc
{
  class TmplSpecScope;
}
namespace smtc
{
  class LinkageSpecScope;
}
namespace smtc
{
  class TmplInstScope;
}
namespace smtc
{
  class LazyClassScope;
}
namespace smtc
{
  class NavClassScope;
}
namespace smtc
{
  class VdfBlockDataScope;
}
namespace smtc
{
  struct ScopeVisitor
  {
    virtual void visit (NsScope const & scope) const;
    virtual void visit (ClassScope const & scope) const;
    virtual void visit (TmplSpecScope const & scope) const;
    virtual void visit (TmplInstScope const & scope) const;
    virtual void visit (LazyClassScope const & scope) const;
    virtual void visit (LinkageSpecScope const & scope) const;
    virtual void visit (NavClassScope const & scope) const;
    virtual void visit (VdfScope const & scope) const;
    virtual void visit (VdfBlockDataScope const & scope) const;
  };
}
#undef LZZ_INLINE
#endif
