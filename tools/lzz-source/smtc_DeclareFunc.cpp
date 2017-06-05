// smtc_DeclareFunc.cpp
//

#include "smtc_DeclareFunc.h"
// semantic
#include "smtc_CheckSpecFlags.h"
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateFrndFuncDeclEntity.h"
#include "smtc_CreateFrndTmplFuncDeclEntity.h"
#include "smtc_CreateFuncDecl.h"
#include "smtc_CreateFuncDeclEntity.h"
#include "smtc_CreateTmplFuncDecl.h"
#include "smtc_CreateTmplFuncDeclEntity.h"
#include "smtc_GetNameLoc.h"
#include "smtc_InstantiateFunc.h"
#include "smtc_IsNameQual.h"
#include "smtc_LinkageSpecScope.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_SpecFlags.h"
#include "smtc_TmplInstScope.h"
#include "smtc_TmplSpecScope.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DeclareFunc : ScopeVisitor
  {
    bool is_tmpl;
    TmplSpecPtrVector & tmpl_spec_set;
    Linkage const & linkage;
    bool is_frnd;
    gram::SpecSel const & spec_sel;
    CvType const & ret_type;
    NamePtr const & name;
    ParamPtrVector const & param_set;
    bool vararg;
    Cv const & cv;
    ThrowSpecPtr const & throw_spec;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void visit (TmplSpecScope const & scope) const;
    void visit (TmplInstScope const & scope) const;
    void visit (LinkageSpecScope const & scope) const;
    EntityPtr buildEntity () const;
  public:
    explicit DeclareFunc (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, Linkage const & linkage, bool is_frnd, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
    ~ DeclareFunc ();
  };
}
namespace
{
  void DeclareFunc::visit (NsScope const & scope) const
    {
      // cannot be a friend func
      if (is_frnd)
      {
        msg::nsFriendFuncDecl (getNameLoc (name));
        return;
      }

      // function cannot be mutable, auto or register
      checkInvalidSpecFlags (spec_sel, MUTABLE_SPEC|AUTO_SPEC|REGISTER_SPEC, msg::invalidFuncSpec);
      // virtual, explicit and pure are not valid namespace func specifiers
      checkInvalidSpecFlags (spec_sel, VIRTUAL_SPEC|EXPLICIT_SPEC|PURE_SPEC, msg::invalidNsFuncSpec);

      if (linkage.isSet ())
      {
        // no storage class specifiers permitted (7.5p7)
        checkInvalidSpecFlags (spec_sel, STATIC_SPEC|EXTERN_SPEC, msg::invalidSpecWithLinkageSpec);
      }
      else
      {
        // static and extern not both valid
        checkConflictingSpecFlags (spec_sel, STATIC_SPEC|EXTERN_SPEC, 0, msg::conflictingFuncSpec);
      }
  
      // add entity to ns
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareFunc::visit (ClassScope const & scope) const
    {
      // function cannot be mutable, auto or register
      checkInvalidSpecFlags (spec_sel, MUTABLE_SPEC|AUTO_SPEC|REGISTER_SPEC, msg::invalidFuncSpec);
      if (is_frnd)
      {
        // virtual, explicit and pure are not valid on friend functions
        checkInvalidSpecFlags (spec_sel, VIRTUAL_SPEC|EXPLICIT_SPEC|PURE_SPEC, msg::invalidFriendFuncSpec);
      }
      else
      {
        // a member decl cannot be qualified
        if (isNameQual (name))
        {
          msg::qualClassFuncDecl (getNameLoc (name));
        }
        // extern is not a valid member func specifier
        checkInvalidSpecFlags (spec_sel, EXTERN_SPEC, msg::invalidClassFuncSpec);
      }

      // add entity to class defn
      scope.getClassDefn ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareFunc::visit (TmplSpecScope const & scope) const
    {
      // declare template function
      tmpl_spec_set.push_back (scope.getTmplSpec ());
      scope.getParent ()->accept (DeclareFunc (true, tmpl_spec_set, linkage, is_frnd, spec_sel, ret_type, name, param_set, vararg, cv, throw_spec));
    }
}
namespace
{
  void DeclareFunc::visit (TmplInstScope const & scope) const
    {
      // instantiate function, cannot be a friend
      if (is_frnd)
      {
        msg::friendFuncInst (getNameLoc (name));
        return;
      }
      instantiateFunc (scope.getParent (), spec_sel, ret_type, param_set, vararg, cv, throw_spec, name);
    }
}
namespace
{
  void DeclareFunc::visit (LinkageSpecScope const & scope) const
    {
      if (linkage.isSet ())
      {
        // nested linkage spec
        msg::multipleLinkageSpec (scope.getLoc ());
      }
      else
      {
        Linkage const & linkage = scope.getLinkage ();
        scope.getParent ()->accept (DeclareFunc (is_tmpl, tmpl_spec_set, linkage, is_frnd, spec_sel, ret_type, name, param_set, vararg, cv, throw_spec));
      }
    }
}
namespace
{
  EntityPtr DeclareFunc::buildEntity () const
    {
      EntityPtr entity;
      int flags = spec_sel.getFlags ();
      if (is_tmpl)
      {
        TmplFuncDeclPtr tmpl_func_decl = createTmplFuncDecl (tmpl_spec_set, linkage, flags, ret_type, name, param_set, vararg, cv, throw_spec);
        entity = is_frnd ? createFrndTmplFuncDeclEntity (tmpl_func_decl) : createTmplFuncDeclEntity (tmpl_func_decl);
      }
      else
      {
        FuncDeclPtr func_decl = createFuncDecl (linkage, flags, ret_type, name, param_set, vararg, cv, throw_spec);
        entity = is_frnd ? createFrndFuncDeclEntity (func_decl) : createFuncDeclEntity (func_decl);
      }
      return entity;
    }
}
namespace
{
  LZZ_INLINE DeclareFunc::DeclareFunc (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, Linkage const & linkage, bool is_frnd, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
    : is_tmpl (is_tmpl), tmpl_spec_set (tmpl_spec_set), linkage (linkage), is_frnd (is_frnd), spec_sel (spec_sel), ret_type (ret_type), name (name), param_set (param_set), vararg (vararg), cv (cv), throw_spec (throw_spec)
         {}
}
namespace
{
  DeclareFunc::~ DeclareFunc ()
         {}
}
namespace smtc
{
  void declareFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
  {
    Linkage linkage;
    TmplSpecPtrVector tmpl_spec_set;
    scope->accept (DeclareFunc (false, tmpl_spec_set, linkage, false, spec_sel, ret_type, name, param_set, vararg, cv, throw_spec));
  }
}
namespace smtc
{
  void declareFrndFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
  {
    Linkage linkage;
    TmplSpecPtrVector tmpl_spec_set;
    scope->accept (DeclareFunc (false, tmpl_spec_set, linkage, true, spec_sel, ret_type, name, param_set, vararg, cv, throw_spec));
  }
}
#undef LZZ_INLINE
