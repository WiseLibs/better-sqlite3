// smtc_OpenLinkageBlock.cpp
//

#include "smtc_OpenLinkageBlock.h"
// semantic
#include "smtc_CreateLinkageNs.h"
#include "smtc_CreateNsEntity.h"
#include "smtc_CreateNsScope.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct OpenLinkageBlock : ScopeVisitor
  {
    util::Loc const & loc;
    util::Ident const & linkage;
    ScopePtr & res_scope;
    void visit (NsScope const & scope) const;
  public:
    explicit OpenLinkageBlock (util::Loc const & loc, util::Ident const & linkage, ScopePtr & res_scope);
    ~ OpenLinkageBlock ();
  };
}
namespace
{
  void OpenLinkageBlock::visit (NsScope const & scope) const
    {
      // create nested namespace and add to enclosing ns
      NsPtr const & encl_ns = scope.getNs ();
      NsPtr ns = createLinkageNs (encl_ns.unref (), loc, linkage);
      encl_ns->addEntity (createNsEntity (ns));
      // create ns scope
      res_scope = createNsScope (ns);
    }
}
namespace
{
  LZZ_INLINE OpenLinkageBlock::OpenLinkageBlock (util::Loc const & loc, util::Ident const & linkage, ScopePtr & res_scope)
    : loc (loc), linkage (linkage), res_scope (res_scope)
         {}
}
namespace
{
  OpenLinkageBlock::~ OpenLinkageBlock ()
         {}
}
namespace smtc
{
  ScopePtr openLinkageBlock (ScopePtr const & encl_scope, util::Loc const & loc, util::Ident const & linkage)
  {
    ScopePtr res_scope;
    encl_scope->accept (OpenLinkageBlock (loc, linkage, res_scope));
    return res_scope;
  }
}
#undef LZZ_INLINE
