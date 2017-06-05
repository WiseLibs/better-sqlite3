// smtc_DefineLazyClass.cpp
//

#include "smtc_DefineLazyClass.h"
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateLazyClass.h"
#include "smtc_CreateLazyClassEntity.h"
#include "smtc_CreateLazyClassScope.h"
#include "smtc_CreateMbrInit.h"
#include "smtc_CreateQualName.h"
#include "smtc_CreateTmplLazyClass.h"
#include "smtc_CreateTmplLazyClassEntity.h"
#include "smtc_DeclareLazyClassObjParamSet.h"
#include "smtc_FormTmplName.h"
#include "smtc_GetNameLoc.h"
#include "smtc_IsNameQual.h"
#include "smtc_LazyBaseSpec.h"
#include "smtc_LazyClass.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_TmplSpecScope.h"
#include "smtc_TmplSpecToArgString.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DefineLazyClass : ScopeVisitor
  {
    bool is_tmpl;
    TmplSpecPtrVector & tmpl_spec_set;
    gram::SpecSel const & spec_sel;
    ClassKey key;
    NamePtr const & name;
    bool is_dll_api;
    ParamPtrVector const & param_set;
    bool vararg;
    BaseSpecPtrVector const & base_spec_set;
    ScopePtr & res_scope;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void visit (TmplSpecScope const & scope) const;
    EntityPtr buildEntity (NamePtr const & encl_qual_name = NamePtr ()) const;
  public:
    explicit DefineLazyClass (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, gram::SpecSel const & spec_sel, ClassKey key, NamePtr const & name, bool is_dll_api, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set, ScopePtr & res_scope);
    ~ DefineLazyClass ();
  };
}
namespace smtc
{
  ScopePtr defineLazyClass (ScopePtr const & scope, gram::SpecSel const & spec_sel, ClassKey key, NamePtr const & name, bool is_dll_api, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set)
  {
    ScopePtr res_scope;
    TmplSpecPtrVector tmpl_spec_set;
    scope->accept (DefineLazyClass (false, tmpl_spec_set, spec_sel, key, name, is_dll_api, param_set, vararg, base_spec_set, res_scope));
    return res_scope;
  }
}
namespace
{
  void DefineLazyClass::visit (NsScope const & scope) const
    {
      // build ns lazy class
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DefineLazyClass::visit (ClassScope const & scope) const
    {
      // cannot be qualified
      if (isNameQual (name))
      {
        msg::qualClassClassDefn (getNameLoc (name));
      }
      // build mbr lazy class
      ClassDefnPtr const & class_defn = scope.getClassDefn ();
      class_defn->addEntity (buildEntity (class_defn->getQualName ()));
    }
}
namespace
{
  void DefineLazyClass::visit (TmplSpecScope const & scope) const
    {
      // declare template class
      tmpl_spec_set.push_back (scope.getTmplSpec ());
      scope.getParent ()->accept (DefineLazyClass (true, tmpl_spec_set, spec_sel, key, name, is_dll_api, param_set,
              vararg, base_spec_set, res_scope));
    }
}
namespace
{
  EntityPtr DefineLazyClass::buildEntity (NamePtr const & encl_qual_name) const
    {
      int flags = spec_sel.getFlags ();
      LazyClassPtr lazy_class = createLazyClass (flags, key, name, is_dll_api, param_set, vararg, base_spec_set);
      declareLazyClassObjParamSet (lazy_class, param_set, base_spec_set);
      // get qual name and entity
      NamePtr qual_name;
      EntityPtr entity;
      if (is_tmpl)
      {
        qual_name = formTmplName (name, tmplSpecToArgString (tmpl_spec_set.front ()));
        TmplLazyClassPtr tmpl_lazy_class = createTmplLazyClass (tmpl_spec_set, lazy_class);
        entity = createTmplLazyClassEntity (tmpl_lazy_class);
      }
      else
      {
        qual_name = name;
        entity = createLazyClassEntity (lazy_class);
      }
      if (encl_qual_name.isSet ())
      {
        qual_name = createQualName (encl_qual_name, qual_name);
      }
      lazy_class->setQualName (qual_name);
      res_scope = createLazyClassScope (lazy_class);
      return entity;
    }
}
namespace
{
  LZZ_INLINE DefineLazyClass::DefineLazyClass (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, gram::SpecSel const & spec_sel, ClassKey key, NamePtr const & name, bool is_dll_api, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set, ScopePtr & res_scope)
    : is_tmpl (is_tmpl), tmpl_spec_set (tmpl_spec_set), spec_sel (spec_sel), key (key), name (name), is_dll_api (is_dll_api), param_set (param_set), vararg (vararg), base_spec_set (base_spec_set), res_scope (res_scope)
         {}
}
namespace
{
  DefineLazyClass::~ DefineLazyClass ()
         {}
}
#undef LZZ_INLINE
