// smtc_DeclareFunctor.cpp
//

#include "smtc_DeclareFunctor.h"
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateAccessSpec.h"
#include "smtc_CreateAccessSpecEntity.h"
#include "smtc_CreateFuncDecl.h"
#include "smtc_CreateFuncDeclEntity.h"
#include "smtc_CreateLazyClass.h"
#include "smtc_CreateLazyClassEntity.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateOperBaseName.h" 
#include "smtc_CreateQualName.h"
#include "smtc_CreateTmplLazyClass.h"
#include "smtc_CreateTmplLazyClassEntity.h"
#include "smtc_DeclareLazyClassObjParamSet.h"
#include "smtc_FormTmplName.h"
#include "smtc_GetNameLoc.h"
#include "smtc_IsNameQual.h"
#include "smtc_LazyClass.h"
#include "smtc_Linkage.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_SpecFlags.h"
#include "smtc_TmplSpecScope.h"
#include "smtc_TmplSpecToArgString.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DeclareFunctor : ScopeVisitor
  {
    bool is_tmpl;
    TmplSpecPtrVector & tmpl_spec_set;
    gram::SpecSel const & spec_sel;
    CvType const & ret_type;
    NamePtr const & name;
    ParamPtrVector const & ctor_param_set;
    bool ctor_vararg;
    ParamPtrVector const & call_param_set;
    bool call_vararg;
    Cv const & cv;
    ThrowSpecPtr const & throw_spec;
    BaseSpecPtrVector const & base_spec_set;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void visit (TmplSpecScope const & scope) const;
    EntityPtr buildEntity (NamePtr const & encl_qual_name = NamePtr ()) const;
    void buildCallDecl (LazyClassPtr const & lazy_class) const;
  public:
    explicit DeclareFunctor (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & ctor_param_set, bool ctor_vararg, ParamPtrVector const & call_param_set, bool call_vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, BaseSpecPtrVector const & base_spec_set);
    ~ DeclareFunctor ();
  };
}
namespace smtc
{
  void declareFunctor (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & ctor_param_set, bool ctor_vararg, ParamPtrVector const & call_param_set, bool call_vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, BaseSpecPtrVector const & base_spec_set)
  {
    TmplSpecPtrVector tmpl_spec_set;
    scope->accept (DeclareFunctor (false, tmpl_spec_set, spec_sel, ret_type, name, ctor_param_set, ctor_vararg, call_param_set,
        call_vararg, cv, throw_spec, base_spec_set));
  }
}
namespace
{
  void DeclareFunctor::visit (NsScope const & scope) const
    {
      // add entity to ns
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareFunctor::visit (ClassScope const & scope) const
    {
      // cannot be qualified
      if (isNameQual (name))
      {
        msg::qualClassClassDefn (getNameLoc (name));
      }
      // add entity to class
      ClassDefnPtr const & class_defn = scope.getClassDefn ();
      class_defn->addEntity (buildEntity (class_defn->getQualName ()));
    }
}
namespace
{
  void DeclareFunctor::visit (TmplSpecScope const & scope) const
    {
      // declare template class
      tmpl_spec_set.push_back (scope.getTmplSpec ());
      scope.getParent ()->accept (DeclareFunctor (true, tmpl_spec_set, spec_sel, ret_type, name, ctor_param_set, ctor_vararg,
                                      call_param_set, call_vararg, cv, throw_spec, base_spec_set));
    }
}
namespace
{
  EntityPtr DeclareFunctor::buildEntity (NamePtr const & encl_qual_name) const
    {
      int flags = 0;
      // create lazy class and declare obj param set
      bool is_dll_api = false;
      LazyClassPtr lazy_class = createLazyClass (flags, STRUCT_KEY, name, is_dll_api, ctor_param_set, ctor_vararg, base_spec_set);
      declareLazyClassObjParamSet (lazy_class, ctor_param_set, base_spec_set);
      buildCallDecl (lazy_class);
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
      return entity;
    }
}
namespace
{
  void DeclareFunctor::buildCallDecl (LazyClassPtr const & lazy_class) const
    {
      // make sure it public
      util::Loc loc = getNameLoc (name);
      // declare operator()
      int flags = spec_sel.getFlags ();
      NamePtr name = createNonTmplName (createOperBaseName (loc, CALL_OPER));
      FuncDeclPtr call_decl = createFuncDecl (Linkage (), flags, ret_type, name, call_param_set, call_vararg, cv, throw_spec);
      lazy_class->addEntity (createFuncDeclEntity (call_decl));
      // if fuctnor is virtual dtor should also be virtual
      if (flags & VIRTUAL_SPEC)
      {
        lazy_class->setVirtualDtor ();
      }
    }
}
namespace
{
  LZZ_INLINE DeclareFunctor::DeclareFunctor (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & ctor_param_set, bool ctor_vararg, ParamPtrVector const & call_param_set, bool call_vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, BaseSpecPtrVector const & base_spec_set)
    : is_tmpl (is_tmpl), tmpl_spec_set (tmpl_spec_set), spec_sel (spec_sel), ret_type (ret_type), name (name), ctor_param_set (ctor_param_set), ctor_vararg (ctor_vararg), call_param_set (call_param_set), call_vararg (call_vararg), cv (cv), throw_spec (throw_spec), base_spec_set (base_spec_set)
         {}
}
namespace
{
  DeclareFunctor::~ DeclareFunctor ()
         {}
}
#undef LZZ_INLINE
