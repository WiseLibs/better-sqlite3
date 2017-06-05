// smtc_DeclareTdef.cpp
//

#include "smtc_DeclareTdef.h"
// semantic
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateTdef.h"
#include "smtc_CreateTdefEntity.h"
#include "smtc_GetNameIfIdent.h"
#include "smtc_GetNameLoc.h"
#include "smtc_IsNameQual.h"
#include "smtc_LinkageSpecScope.h"
#include "smtc_Message.h"
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
  struct DeclareTdef : ScopeVisitor
  {
    Linkage const & linkage;
    CvType const & cv_type;
    NamePtr const & name;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void visit (LinkageSpecScope const & scope) const;
    void checkName () const;
    void visit (TmplSpecScope const & scope) const;
    void visit (TmplInstScope const & scope) const;
    EntityPtr buildEntity () const;
  public:
    explicit DeclareTdef (Linkage const & linkage, CvType const & cv_type, NamePtr const & name);
    ~ DeclareTdef ();
  };
}
namespace
{
  void DeclareTdef::visit (NsScope const & scope) const
    {
      // check name
      checkName ();

      // add entity namespace
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareTdef::visit (ClassScope const & scope) const
    {
      // check name
      checkName ();

      // store type name in scope
      ClassDefnPtr const & class_defn = scope.getClassDefn ();
      util::Ident ident = getNameIfIdent (name);
      if (ident.isSet ())
      {
        class_defn->addTypeName (ident);
      }

      // add entity class
      class_defn->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareTdef::visit (LinkageSpecScope const & scope) const
    {
      if (linkage.isSet ())
      {
        // nested linkage spec
        msg::multipleLinkageSpec (scope.getLoc ());
      }
      else
      {
        Linkage const & linkage = scope.getLinkage ();
        scope.getParent ()->accept (DeclareTdef (linkage, cv_type, name));
      }
    }
}
namespace
{
  void DeclareTdef::checkName () const
    {
      // cannot be qualfied
      if (isNameQual (name))
      {
        msg::qualTdef (getNameLoc (name));
      }
    }
}
namespace
{
  void DeclareTdef::visit (TmplSpecScope const & scope) const
    {
      // cannot declare a template typedef
      msg::templateTdef (getNameLoc (name));
    }
}
namespace
{
  void DeclareTdef::visit (TmplInstScope const & scope) const
    {
      // cannot explicitly instantiate a typedef
      msg::instantiateTdef (getNameLoc (name));
    }
}
namespace
{
  EntityPtr DeclareTdef::buildEntity () const
    {
      TdefPtr tdef = createTdef (linkage, cv_type, name);
      return createTdefEntity (tdef);
    }
}
namespace
{
  LZZ_INLINE DeclareTdef::DeclareTdef (Linkage const & linkage, CvType const & cv_type, NamePtr const & name)
    : linkage (linkage), cv_type (cv_type), name (name)
         {}
}
namespace
{
  DeclareTdef::~ DeclareTdef ()
         {}
}
namespace smtc
{
  void declareTdef (ScopePtr const & scope, CvType const & cv_type, NamePtr const & name)
  {
    Linkage linkage;
    scope->accept (DeclareTdef (linkage, cv_type, name));
  }
}
#undef LZZ_INLINE
