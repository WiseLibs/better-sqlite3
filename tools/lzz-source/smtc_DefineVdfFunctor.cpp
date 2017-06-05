// smtc_DefineVdfFunctor.cpp
//

#include "smtc_DefineVdfFunctor.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_ClassDefn.h"
#include "smtc_CreateAccessSpec.h"
#include "smtc_CreateAccessSpecEntity.h"
#include "smtc_CreateBaseSpec.h"
#include "smtc_CreateClassDefn.h"
#include "smtc_CreateClassDefnEntity.h"
#include "smtc_CreateCtorInit.h"
#include "smtc_CreateDtorBaseName.h"
#include "smtc_CreateFuncDefn.h"
#include "smtc_CreateFuncDefnEntity.h"
#include "smtc_CreateMbrInit.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateObj.h"
#include "smtc_CreateObjEntity.h"
#include "smtc_CreateOperBaseName.h"
#include "smtc_CreateTmplClassDefn.h"
#include "smtc_CreateTmplClassDefnEntity.h"
#include "smtc_FormTmplName.h"
#include "smtc_GetCvTypeAsConst.h"
#include "smtc_GetNameIfIdent.h"
#include "smtc_GetNameLoc.h"
#include "smtc_Linkage.h"
#include "smtc_NameToString.h"
#include "smtc_NonTypeParam.h"
#include "smtc_Ns.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_SpecFlags.h"
#include "smtc_TmplSpecScope.h"
#include "smtc_TmplSpecToArgString.h"
#include "smtc_VdfScope.h"

// gram
#include "gram_CharBlock.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct BuildMbrInitFromParam
  {
    MbrInitPtr operator () (ParamPtr const & param) const;
  public:
    explicit BuildMbrInitFromParam ();
    ~ BuildMbrInitFromParam ();
  };
}
namespace
{
  struct DefineParamAsConstMbrObj
  {
    ClassDefnPtr const & class_defn;
    void operator () (ParamPtr const & param) const;
  public:
    explicit DefineParamAsConstMbrObj (ClassDefnPtr const & class_defn);
    ~ DefineParamAsConstMbrObj ();
  };
}
namespace
{
  struct DefineVdfFunctor : ScopeVisitor
  {
    bool is_tmpl;
    TmplSpecPtrVector & tmpl_spec_set;
    NamePtr const & name;
    ParamPtrVector const & param_set;
    bool vararg;
    gram::Block const & body;
    TryBlockPtr const & try_block;
    void visit (VdfScope const & scope) const;
    void visit (TmplSpecScope const & scope) const;
  public:
    explicit DefineVdfFunctor (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, gram::Block const & body, TryBlockPtr const & try_block);
    ~ DefineVdfFunctor ();
  };
}
namespace
{
  MbrInitPtr BuildMbrInitFromParam::operator () (ParamPtr const & param) const
  {
    NamePtr const & name = param->getName ();
    return createMbrInit (name, nameToString (name));
  }
}
namespace
{
  LZZ_INLINE BuildMbrInitFromParam::BuildMbrInitFromParam ()
             {}
}
namespace
{
  BuildMbrInitFromParam::~ BuildMbrInitFromParam ()
             {}
}
namespace
{
  void DefineParamAsConstMbrObj::operator () (ParamPtr const & param) const
  {
    NonTypeParam const & non_type_param = static_cast <NonTypeParam const &> (* param);
    NamePtr const & name = non_type_param.getName ();
    CvType param_type = getCvTypeAsConst (non_type_param.getCvType ());
    ObjPtr obj = createObj (0, param_type, name, InitPtr ());
    class_defn->addEntity (createObjEntity (obj));
  }
}
namespace
{
  LZZ_INLINE DefineParamAsConstMbrObj::DefineParamAsConstMbrObj (ClassDefnPtr const & class_defn)
    : class_defn (class_defn)
       {}
}
namespace
{
  DefineParamAsConstMbrObj::~ DefineParamAsConstMbrObj ()
       {}
}
namespace
{
  void DefineVdfFunctor::visit (VdfScope const & scope) const
    {
      // define class in private ns
      NsPtr const & ns = scope.getPrivateNs ();
      BaseSpecPtrVector base_spec_set;
      base_spec_set.push_back (createBaseSpec (DEFAULT_ACCESS, false, scope.getBaseTypeName ()));
      bool is_dll_api = false;
      ClassDefnPtr class_defn = createClassDefn (STRUCT_KEY, name, is_dll_api, base_spec_set);
      NamePtr qual_name;
      EntityPtr entity;
      if (is_tmpl)
      {
        qual_name = formTmplName (name, tmplSpecToArgString (tmpl_spec_set.front ()));
        TmplClassDefnPtr tmpl_class_defn = createTmplClassDefn (tmpl_spec_set, class_defn);
        entity = createTmplClassDefnEntity (tmpl_class_defn);
      }
      else
      {
        qual_name = name;
        entity = createClassDefnEntity (class_defn);
      }
      class_defn->setQualName (qual_name);
      ns->addEntity (entity);
      util::Loc name_loc = getNameLoc (name);
      // define ctor with explicit spec
      MbrInitPtrVector mbr_init_set;
      std::transform (param_set.begin (), param_set.end (), std::back_inserter (mbr_init_set), BuildMbrInitFromParam ());
      CtorInitPtr ctor_init;
      if (! mbr_init_set.empty ())
      {
        ctor_init = createCtorInit (name_loc, mbr_init_set);
      }
      FuncDefnPtr func_defn = createFuncDefn (Linkage (), EXPLICIT_SPEC, CvType (), name, param_set, false, Cv (), ThrowSpecPtr (),
          ctor_init, gram::CharBlock (name_loc), TryBlockPtr ());
      class_defn->addEntity (createFuncDefnEntity (func_defn));
      // dtor
      util::Ident ident = getNameIfIdent (name);
      NamePtr dtor_name = createNonTmplName (createDtorBaseName (name_loc, ident));
      func_defn = createFuncDefn (Linkage (), 0, CvType (), dtor_name, ParamPtrVector (), false, Cv (), ThrowSpecPtr (),
          CtorInitPtr (), gram::CharBlock (name_loc), TryBlockPtr ());
      class_defn->addEntity (createFuncDefnEntity (func_defn));
      // define functor, no specifiers, get args from scope, same as functor in base vdf  
      func_defn = createFuncDefn (Linkage (), 0, scope.getReturnType (), scope.getName (), scope.getParamSet (), scope.hasVarArg (),
          Cv (true, false), scope.getThrowSpec (), CtorInitPtr (), body, try_block);
      class_defn->addEntity (createFuncDefnEntity (func_defn));
      // declare member objs as private
      class_defn->addEntity (createAccessSpecEntity (createAccessSpec (name_loc, PRIVATE_ACCESS)));
      std::for_each (param_set.begin (), param_set.end (), DefineParamAsConstMbrObj (class_defn));
    }
}
namespace
{
  void DefineVdfFunctor::visit (TmplSpecScope const & scope) const
    {
      // define template function
      tmpl_spec_set.push_back (scope.getTmplSpec ());
      scope.getParent ()->accept (DefineVdfFunctor (true, tmpl_spec_set, name, param_set, vararg, body, try_block));
    }
}
namespace
{
  LZZ_INLINE DefineVdfFunctor::DefineVdfFunctor (bool is_tmpl, TmplSpecPtrVector & tmpl_spec_set, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, gram::Block const & body, TryBlockPtr const & try_block)
    : is_tmpl (is_tmpl), tmpl_spec_set (tmpl_spec_set), name (name), param_set (param_set), vararg (vararg), body (body), try_block (try_block)
         {}
}
namespace
{
  DefineVdfFunctor::~ DefineVdfFunctor ()
         {}
}
namespace smtc
{
  void defineVdfFunctor (ScopePtr const & scope, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, gram::Block const & body, TryBlockPtr const & try_block)
  {
    TmplSpecPtrVector tmpl_spec_set;
    scope->accept (DefineVdfFunctor (false, tmpl_spec_set, name, param_set, vararg, body, try_block));
  }
}
#undef LZZ_INLINE
