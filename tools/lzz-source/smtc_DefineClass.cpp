// smtc_DefineClass.cpp
//

#include "smtc_DefineClass.h"
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateClassDefn.h"
#include "smtc_CreateClassDefnEntity.h"
#include "smtc_CreateClassScope.h"
#include "smtc_CreateQualName.h"
#include "smtc_CreateTmplClassDefn.h"
#include "smtc_CreateTmplClassDefnEntity.h"
#include "smtc_FormTmplName.h"
#include "smtc_GetNameIfIdent.h"
#include "smtc_GetNameLoc.h"
#include "smtc_IsExplicitTmplSpec.h"
#include "smtc_IsNameQual.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_TmplClassDefn.h"
#include "smtc_TmplSpecScope.h"
#include "smtc_TmplSpecToArgString.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DefineClass : ScopeVisitor
  {
    bool is_tmpl;
    TmplSpecPtrVector & tmpl_spec_set;
    ClassKey key;
    NamePtr const & name;
    bool is_dll_api;
    BaseSpecPtrVector const & base_spec_set;
    ScopePtr & res_scope;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void visit (TmplSpecScope const & scope) const;
    EntityPtr buildEntity (NamePtr const & encl_qual_name = NamePtr ()) const;
  public:
    explicit DefineClass (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, ClassKey key, NamePtr const & name, bool is_dll_api, BaseSpecPtrVector const & base_spec_set, ScopePtr & res_scope);
    ~ DefineClass ();
  };
}
namespace
{
  void DefineClass::visit (NsScope const & scope) const
    {
      // build ns class defn
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DefineClass::visit (ClassScope const & scope) const
    {
      // cannot be qualified
      if (isNameQual (name))
      {
        msg::qualClassClassDefn (getNameLoc (name));
      }
      
      // store type name in scope if not tmpl
      ClassDefnPtr const & class_defn = scope.getClassDefn ();
      util::Ident ident = getNameIfIdent (name);
      if (ident.isSet ())
      {
        class_defn->addTypeName (ident);
      }

      // build mbr class defn
      class_defn->addEntity (buildEntity (class_defn->getQualName ()));
    }
}
namespace
{
  void DefineClass::visit (TmplSpecScope const & scope) const
    {
      // declare template class
      tmpl_spec_set.push_back (scope.getTmplSpec ());
      scope.getParent ()->accept (DefineClass (true, tmpl_spec_set, key, name, is_dll_api, base_spec_set, res_scope));
    }
}
namespace
{
  EntityPtr DefineClass::buildEntity (NamePtr const & encl_qual_name) const
    {
      ClassDefnPtr class_defn = createClassDefn (key, name, is_dll_api, base_spec_set);
      NamePtr qual_name;
      EntityPtr entity;
      if (is_tmpl)
      {
        qual_name = formTmplName (name, tmplSpecToArgString (tmpl_spec_set.front ()));
        TmplClassDefnPtr tmpl_class_defn = createTmplClassDefn (tmpl_spec_set, class_defn);
        entity = createTmplClassDefnEntity (tmpl_class_defn);
        // dependent class (return types prefixed by typename)
        if (! isExplicitTmplSpec (tmpl_spec_set))
        {
          class_defn->setDependent ();
        }
      }
      else
      {
        qual_name = name;
        entity = createClassDefnEntity (class_defn);
      }
      if (encl_qual_name.isSet ())
      {
        qual_name = createQualName (encl_qual_name, qual_name);
      }
      class_defn->setQualName (qual_name);
      res_scope = createClassScope (class_defn);
      return entity;
    }
}
namespace
{
  LZZ_INLINE DefineClass::DefineClass (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, ClassKey key, NamePtr const & name, bool is_dll_api, BaseSpecPtrVector const & base_spec_set, ScopePtr & res_scope)
    : is_tmpl (is_tmpl), tmpl_spec_set (tmpl_spec_set), key (key), name (name), is_dll_api (is_dll_api), base_spec_set (base_spec_set), res_scope (res_scope)
         {}
}
namespace
{
  DefineClass::~ DefineClass ()
         {}
}
namespace smtc
{
  ScopePtr defineClass (ScopePtr const & scope, ClassKey key, NamePtr const & name, bool is_dll_api, BaseSpecPtrVector const & base_spec_set)
  {
    ScopePtr res_scope;
    TmplSpecPtrVector tmpl_spec_set;
    scope->accept (DefineClass (false, tmpl_spec_set, key, name, is_dll_api, base_spec_set, res_scope));
    return res_scope;
  }
}
#undef LZZ_INLINE
