// smtc_DefineVdf.cpp
//

#include "smtc_DefineVdf.h"
// semantic
#include "smtc_ClassDefn.h"
#include "smtc_CreateClassDefn.h"
#include "smtc_CreateDtorBaseName.h"
#include "smtc_CreateFuncDecl.h"
#include "smtc_CreateFuncDeclEntity.h"
#include "smtc_CreateFuncDefn.h"
#include "smtc_CreateFuncDefnEntity.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateNsEntity.h"
#include "smtc_CreateOperBaseName.h"
#include "smtc_CreateUnnamedNs.h"
#include "smtc_CreateVdfClassEntity.h"
#include "smtc_CreateVdfScope.h"
#include "smtc_GetNameIfIdent.h"
#include "smtc_GetNameLoc.h"
#include "smtc_Linkage.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_SpecFlags.h"

// gram
#include "gram_CharBlock.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DefineVdf : ScopeVisitor
  {
    gram::SpecSel const & spec_sel;
    CvType const & ret_type;
    NamePtr const & name;
    ParamPtrVector const & param_set;
    bool vararg;
    ThrowSpecPtr const & throw_spec;
    ScopePtr & res_scope;
    void visit (NsScope const & scope) const;
    EntityPtr createVdfDtor () const;
  public:
    explicit DefineVdf (gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, ThrowSpecPtr const & throw_spec, ScopePtr & res_scope);
    ~ DefineVdf ();
  };
}
namespace
{
  void DefineVdf::visit (NsScope const & scope) const
    {
      // define vdf class in namespace
      NsPtr const & ns = scope.getNs ();
      bool is_dll_api = false;
      ClassDefnPtr class_defn = createClassDefn (STRUCT_KEY, name, is_dll_api, BaseSpecPtrVector ());
      class_defn->setQualName (name);
      ns->addEntity (createVdfClassEntity (class_defn));
      // add virtual dtor
      class_defn->addEntity (createVdfDtor ());
      // add operator() call to class defn, call is const, no throw specification, pure virtual only
      NamePtr func_name = createNonTmplName (createOperBaseName (getNameLoc (name), CALL_OPER));
      Cv cv (true, false);
      FuncDeclPtr func_decl = createFuncDecl (Linkage (), VIRTUAL_SPEC|PURE_SPEC, ret_type, func_name, param_set, vararg, cv, ThrowSpecPtr ());
      class_defn->addEntity (createFuncDeclEntity (func_decl));
      // create private ns as child of outer ns, use location of name
      NsPtr private_ns = createUnnamedNs (ns.unref (), getNameLoc (name));
      ns->addEntity (createNsEntity (private_ns));
      // save return type, names and param set for derived classes
      res_scope = createVdfScope (ns, name, ret_type, func_name, param_set, vararg, throw_spec, private_ns);
    }
}
namespace
{
  EntityPtr DefineVdf::createVdfDtor () const
    {
      int flags = VIRTUAL_SPEC|PURE_SPEC;
      util::Ident ident = getNameIfIdent (name);
      util::Loc name_loc = getNameLoc (name); 
      NamePtr dtor_name = createNonTmplName (createDtorBaseName (name_loc, ident));
      FuncDefnPtr func_defn = createFuncDefn (Linkage (), flags, CvType (), dtor_name, ParamPtrVector (), false, Cv (),
          ThrowSpecPtr (), CtorInitPtr (), gram::CharBlock (name_loc), TryBlockPtr ());
      return createFuncDefnEntity (func_defn);
    }
}
namespace
{
  LZZ_INLINE DefineVdf::DefineVdf (gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, ThrowSpecPtr const & throw_spec, ScopePtr & res_scope)
    : spec_sel (spec_sel), ret_type (ret_type), name (name), param_set (param_set), vararg (vararg), throw_spec (throw_spec), res_scope (res_scope)
         {}
}
namespace
{
  DefineVdf::~ DefineVdf ()
         {}
}
namespace smtc
{
  ScopePtr defineVdf (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, ThrowSpecPtr const & throw_spec)
  {
    ScopePtr res_scope;
    scope->accept (DefineVdf (spec_sel, ret_type, name, param_set, vararg, throw_spec, res_scope));
    return res_scope;
  }
}
#undef LZZ_INLINE
