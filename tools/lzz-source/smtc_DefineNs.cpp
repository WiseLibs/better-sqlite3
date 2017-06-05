// smtc_DefineNs.cpp
//

#include "smtc_DefineNs.h"
// semantic
#include "smtc_BaseName.h"
#include "smtc_CreateNamedNs.h"
#include "smtc_CreateNsEntity.h"
#include "smtc_CreateNsScope.h"
#include "smtc_CreateUnnamedNs.h"
#include "smtc_GetNameLoc.h"
#include "smtc_Message.h"
#include "smtc_NameVisitor.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_QualName.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_TmplName.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct CheckNsName : NameVisitor
  {
    void visit (QualName const & name) const;
    void visit (TmplName const & name) const;
  public:
    explicit CheckNsName ();
    ~ CheckNsName ();
  };
}
namespace
{
  struct DefineNs : ScopeVisitor
  {
    util::Loc const & loc;
    NamePtr const & name;
    ScopePtr & res_scope;
    void visit (NsScope const & scope) const;
  public:
    explicit DefineNs (util::Loc const & loc, NamePtr const & name, ScopePtr & res_scope);
    ~ DefineNs ();
  };
}
namespace
{
  void CheckNsName::visit (QualName const & name) const
    {
      NamePtr const & qual_name = name.getQualName ();
      NamePtr const & unql_name = name.getUnqlName ();
      if (! qual_name.isSet ())
      {
        msg::fileQualNs (getNameLoc (unql_name));
      }
      else
      {
        qual_name->accept (* this);
      }
      unql_name->accept (* this);
    }
}
namespace
{
  void CheckNsName::visit (TmplName const & name) const
    {
      msg::templateNs (name.getBaseName ()->getLoc ());
    }
}
namespace
{
  LZZ_INLINE CheckNsName::CheckNsName ()
         {}
}
namespace
{
  CheckNsName::~ CheckNsName ()
         {}
}
namespace
{
  void DefineNs::visit (NsScope const & scope) const
    {
      NsPtr ns;
      NsPtr const & encl_ns = scope.getNs ();
      // check name
      if (name.isSet ())
      {
        name->accept (CheckNsName ());
        ns = createNamedNs (encl_ns.unref (), loc, name);
      }
      else
      {
        ns = createUnnamedNs (encl_ns.unref (), loc);
      }
      // create nested namespace and add to enclosing ns
      encl_ns->addEntity (createNsEntity (ns));

      // create ns scope
      res_scope = createNsScope (ns);
    }
}
namespace
{
  LZZ_INLINE DefineNs::DefineNs (util::Loc const & loc, NamePtr const & name, ScopePtr & res_scope)
    : loc (loc), name (name), res_scope (res_scope)
         {}
}
namespace
{
  DefineNs::~ DefineNs ()
         {}
}
namespace smtc
{
  ScopePtr defineNs (ScopePtr const & scope, util::Loc const & loc, NamePtr const & name)
  {
    ScopePtr res_scope;
    scope->accept (DefineNs (loc, name, res_scope));
    return res_scope;
  }
}
namespace smtc
{
  ScopePtr defineUnnamedNs (ScopePtr const & scope, util::Loc const & loc)
  {
    return defineNs (scope, loc, NamePtr ());
  }
}
#undef LZZ_INLINE
