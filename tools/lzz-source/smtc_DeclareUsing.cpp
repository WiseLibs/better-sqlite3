// smtc_DeclareUsing.cpp
//

#include "smtc_DeclareUsing.h"
// semantic
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateUsingDecl.h"
#include "smtc_CreateUsingDeclEntity.h"
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
  struct DeclareUsing : ScopeVisitor
  {
    NamePtr const & name;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    EntityPtr buildEntity () const;
  public:
    explicit DeclareUsing (NamePtr const & name);
    ~ DeclareUsing ();
  };
}
namespace
{
  void DeclareUsing::visit (NsScope const & scope) const
    {
      // add entity to ns
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareUsing::visit (ClassScope const & scope) const
    {
      // add entity to class
      scope.getClassDefn ()->addEntity (buildEntity ());
    }
}
namespace
{
  EntityPtr DeclareUsing::buildEntity () const
    {
      UsingDeclPtr using_decl = createUsingDecl (name);
      return createUsingDeclEntity (using_decl);
    }
}
namespace
{
  LZZ_INLINE DeclareUsing::DeclareUsing (NamePtr const & name)
    : name (name)
         {}
}
namespace
{
  DeclareUsing::~ DeclareUsing ()
         {}
}
namespace smtc
{
  void declareUsing (ScopePtr const & scope, NamePtr const & name)
  {
    scope->accept (DeclareUsing (name));
  }
}
#undef LZZ_INLINE
