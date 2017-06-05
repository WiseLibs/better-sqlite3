// smtc_DefineFunc.cpp
//

#include "smtc_DefineFunc.h"
// semantic
#include "smtc_CheckSpecFlags.h"
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateFrndFuncDefnEntity.h"
#include "smtc_CreateFrndTmplFuncDefnEntity.h"
#include "smtc_CreateFuncDefn.h"
#include "smtc_CreateFuncDefnEntity.h"
#include "smtc_CreateTmplFuncDefn.h"
#include "smtc_CreateTmplFuncDefnEntity.h"
#include "smtc_FuncDefn.h"
#include "smtc_GetNameLoc.h"
#include "smtc_IsNameQual.h"
#include "smtc_LinkageSpecScope.h"
#include "smtc_Message.h"
#include "smtc_NavClassScope.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_QualifyType.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_SpecFlags.h"
#include "smtc_TmplSpecScope.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DefineFunc : ScopeVisitor
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
    CtorInitPtr const & ctor_init;
    gram::Block const & body;
    TryBlockPtr const & try_block;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void visit (NavClassScope const & scope) const;
    void visit (TmplSpecScope const & scope) const;
    void visit (LinkageSpecScope const & scope) const;
    void checkClassNameAndFlags () const;
    EntityPtr buildEntity (CvType const & alt_ret_type = CvType (), bool as_const = false) const;
  public:
    explicit DefineFunc (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, Linkage const & linkage, bool is_frnd, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block);
    ~ DefineFunc ();
  };
}
namespace
{
  void DefineFunc::visit (NsScope const & scope) const
    {
      if (is_frnd)
      {
        msg::nsFriendFuncDefn (getNameLoc (name));
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
  void DefineFunc::visit (ClassScope const & scope) const
    {
      // check name and flags for class function
      checkClassNameAndFlags ();

      // alt return type used for out of class definition, only applies to non-friend functions
      ClassDefnPtr const & class_defn = scope.getClassDefn ();
      CvType alt_ret_type;
      if (! is_frnd && ret_type.isSet ())
      {
        qualifyType (ret_type, class_defn->getTypeNameSet (), class_defn->getQualName (), class_defn->isDependent (), alt_ret_type);
      }

      // add entity to class defn
      class_defn->addEntity (buildEntity (alt_ret_type));
    }
}
namespace
{
  void DefineFunc::visit (NavClassScope const & scope) const
    {
      // check name and flags for class function
      checkClassNameAndFlags ();

      // add entity to class defn, const if not friend
      bool as_const = ! (is_frnd || spec_sel.hasSpec (STATIC_SPEC));
      scope.getClassDefn ()->addEntity (buildEntity (CvType (), as_const));
    }
}
namespace
{
  void DefineFunc::visit (TmplSpecScope const & scope) const
    {
      // define template function
      tmpl_spec_set.push_back (scope.getTmplSpec ());
      scope.getParent ()->accept (DefineFunc (true, tmpl_spec_set, linkage, is_frnd, spec_sel, ret_type, name, param_set, vararg, cv,
                                      throw_spec, ctor_init, body, try_block));
    }
}
namespace
{
  void DefineFunc::visit (LinkageSpecScope const & scope) const
    {
      if (linkage.isSet ())
      {
        // nested linkage spec
        msg::multipleLinkageSpec (scope.getLoc ());
      }
      else
      {
        Linkage const & linkage = scope.getLinkage ();
        scope.getParent ()->accept (DefineFunc (is_tmpl, tmpl_spec_set, linkage, is_frnd, spec_sel, ret_type, name, param_set, vararg, cv,
                                        throw_spec, ctor_init, body, try_block));
      }
    }
}
namespace
{
  void DefineFunc::checkClassNameAndFlags () const
    {
      // cannot be qualified
      if (isNameQual (name))
      {
        (is_frnd ? msg::qualFriendFuncDefn : msg::qualClassFuncDefn) (getNameLoc (name));
      }
      // function cannot be mutable, auto or register
      checkInvalidSpecFlags (spec_sel, MUTABLE_SPEC|AUTO_SPEC|REGISTER_SPEC, msg::invalidFuncSpec);
      if (is_frnd)
      {
        // virtual, explicit and pure are not valid on friend functions
        checkInvalidSpecFlags (spec_sel, VIRTUAL_SPEC|EXPLICIT_SPEC|PURE_SPEC, msg::invalidFriendFuncSpec);
      }
      else
      {
        // extern is not a valid member func specifier
        checkInvalidSpecFlags (spec_sel, EXTERN_SPEC, msg::invalidClassFuncSpec);
      }
    }
}
namespace
{
  EntityPtr DefineFunc::buildEntity (CvType const & alt_ret_type, bool as_const) const
    {
      int flags = spec_sel.getFlags ();
      Cv alt_cv (as_const | cv.isConst (), cv.isVolatile ());
      FuncDefnPtr func_defn = createFuncDefn (linkage, flags, ret_type, name, param_set, vararg, alt_cv, throw_spec, ctor_init, body, try_block);
      func_defn->setAltReturnType (alt_ret_type);
      EntityPtr entity;
      if (is_tmpl)
      {
        TmplFuncDefnPtr tmpl_func_defn = createTmplFuncDefn (tmpl_spec_set, func_defn);
        entity = is_frnd ? createFrndTmplFuncDefnEntity (tmpl_func_defn) : createTmplFuncDefnEntity (tmpl_func_defn);
      }
      else
      {
        entity = is_frnd ? createFrndFuncDefnEntity (func_defn) : createFuncDefnEntity (func_defn);
      }
      return entity;
    }
}
namespace
{
  LZZ_INLINE DefineFunc::DefineFunc (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, Linkage const & linkage, bool is_frnd, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block)
    : is_tmpl (is_tmpl), tmpl_spec_set (tmpl_spec_set), linkage (linkage), is_frnd (is_frnd), spec_sel (spec_sel), ret_type (ret_type), name (name), param_set (param_set), vararg (vararg), cv (cv), throw_spec (throw_spec), ctor_init (ctor_init), body (body), try_block (try_block)
         {}
}
namespace
{
  DefineFunc::~ DefineFunc ()
         {}
}
namespace smtc
{
  void defineFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block)
  {
    TmplSpecPtrVector tmpl_spec_set;
    Linkage linkage;
    scope->accept (DefineFunc (false, tmpl_spec_set, linkage, false, spec_sel, ret_type, name, param_set, vararg, cv,
                       throw_spec, ctor_init, body, try_block));
  }
}
namespace smtc
{
  void defineFrndFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block)
  {
    TmplSpecPtrVector tmpl_spec_set;
    Linkage linkage;
    scope->accept (DefineFunc (false, tmpl_spec_set, linkage, true, spec_sel, ret_type, name, param_set, vararg, cv,
                       throw_spec, ctor_init, body, try_block));
  }
}
#undef LZZ_INLINE
