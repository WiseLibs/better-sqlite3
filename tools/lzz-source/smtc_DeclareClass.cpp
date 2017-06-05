// smtc_DeclareClass.cpp
//

#include "smtc_DeclareClass.h"
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateClassDecl.h"
#include "smtc_CreateClassDeclEntity.h"
#include "smtc_CreateFrndClassDeclEntity.h"
#include "smtc_CreateFrndTmplClassDeclEntity.h"
#include "smtc_CreateTmplClassDecl.h"
#include "smtc_CreateTmplClassDeclEntity.h"
#include "smtc_GetNameIfIdent.h"
#include "smtc_InstantiateClass.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_TmplInstScope.h"
#include "smtc_TmplSpec.h"
#include "smtc_TmplSpecScope.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DeclareClass : ScopeVisitor
  {
    bool is_tmpl;
    TmplSpecPtrVector & tmpl_spec_set;
    bool is_frnd;
    ClassKey key;
    NamePtr const & name;
    bool is_dll_api;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void visit (TmplSpecScope const & scope) const;
    void visit (TmplInstScope const & scope) const;
    EntityPtr buildEntity () const;
  public:
    explicit DeclareClass (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, bool is_frnd, ClassKey key, NamePtr const & name, bool is_dll_api);
    ~ DeclareClass ();
  };
}
namespace smtc
{
  void declareClass (ScopePtr const & scope, ClassKey key, NamePtr const & name, bool is_dll_api)
  {
    TmplSpecPtrVector tmpl_spec_set;
    scope->accept (DeclareClass (false, tmpl_spec_set, false, key, name, is_dll_api));
  }
}
namespace smtc
{
  void declareFrndClass (ScopePtr const & scope, ClassKey key, NamePtr const & name)
  {
    TmplSpecPtrVector tmpl_spec_set;
    bool is_dll_api = false;
    scope->accept (DeclareClass (false, tmpl_spec_set, true, key, name, is_dll_api));
  }
}
namespace
{
  void DeclareClass::visit (NsScope const & scope) const
    {
      // TBD: check name
      // ... 

      // create class decl and add to namespace
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareClass::visit (ClassScope const & scope) const
    {
      // TBD: check name
      // ...

      // store type name in scope if not tmpl
      ClassDefnPtr const & class_defn = scope.getClassDefn ();
      util::Ident ident = getNameIfIdent (name);
      if (ident.isSet ())
      {
        class_defn->addTypeName (ident);
      }

      // create class decl and add to class defn
      scope.getClassDefn ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareClass::visit (TmplSpecScope const & scope) const
    {
      // declare template class
      tmpl_spec_set.push_back (scope.getTmplSpec ());
      scope.getParent ()->accept (DeclareClass (true, tmpl_spec_set, is_frnd, key, name, is_dll_api));
    }
}
namespace
{
  void DeclareClass::visit (TmplInstScope const & scope) const
    {
      instantiateClass (scope.getParent (), key, name, is_dll_api);
    }
}
namespace
{
  EntityPtr DeclareClass::buildEntity () const
    {
      EntityPtr entity;
      if (is_tmpl)
      {
        TmplClassDeclPtr tmpl_class_decl = createTmplClassDecl (tmpl_spec_set, key, name);
        entity = is_frnd ? createFrndTmplClassDeclEntity (tmpl_class_decl) : createTmplClassDeclEntity (tmpl_class_decl);
      }
      else
      {
        ClassDeclPtr class_decl = createClassDecl (key, name, is_dll_api);
        entity = is_frnd ? createFrndClassDeclEntity (class_decl) : createClassDeclEntity (class_decl);
      }
      return entity;
    }
}
namespace
{
  LZZ_INLINE DeclareClass::DeclareClass (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, bool is_frnd, ClassKey key, NamePtr const & name, bool is_dll_api)
    : is_tmpl (is_tmpl), tmpl_spec_set (tmpl_spec_set), is_frnd (is_frnd), key (key), name (name), is_dll_api (is_dll_api)
         {}
}
namespace
{
  DeclareClass::~ DeclareClass ()
         {}
}
#undef LZZ_INLINE
