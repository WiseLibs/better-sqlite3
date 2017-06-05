// smtc_InstantiateFunc.cpp
//

#include "smtc_InstantiateFunc.h"
// semantic
#include "smtc_CheckSpecFlags.h"
#include "smtc_CreateFuncDecl.h"
#include "smtc_CreateFuncInstEntity.h"
#include "smtc_Linkage.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_SpecFlags.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct InstantiateFunc : ScopeVisitor
  {
    gram::SpecSel const & spec_sel;
    CvType const & ret_type;
    ParamPtrVector const & param_set;
    bool vararg;
    Cv const & cv;
    ThrowSpecPtr const & throw_spec;
    NamePtr const & name;
    void visit (NsScope const & scope) const;
  public:
    explicit InstantiateFunc (gram::SpecSel const & spec_sel, CvType const & ret_type, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, NamePtr const & name);
    ~ InstantiateFunc ();
  };
}
namespace
{
  void InstantiateFunc::visit (NsScope const & scope) const
    {
      // function cannot be mutable, auto or register
      checkInvalidSpecFlags (spec_sel, MUTABLE_SPEC|AUTO_SPEC|REGISTER_SPEC, msg::invalidFuncSpec);
      // virtual, explicit and pure are not valid namespace func specifiers
      checkInvalidSpecFlags (spec_sel, VIRTUAL_SPEC|EXPLICIT_SPEC|PURE_SPEC, msg::invalidNsFuncSpec);
      // object cannot be both static and extern
      checkConflictingSpecFlags (spec_sel, STATIC_SPEC|EXTERN_SPEC, 0, msg::conflictingFuncSpec);

      // create func decl and add to namespace
      int flags = spec_sel.getFlags ();
      FuncDeclPtr func_decl = createFuncDecl (Linkage (), flags, ret_type, name, param_set, vararg, cv, throw_spec);
      scope.getNs ()->addEntity (createFuncInstEntity (func_decl));
    }
}
namespace
{
  LZZ_INLINE InstantiateFunc::InstantiateFunc (gram::SpecSel const & spec_sel, CvType const & ret_type, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, NamePtr const & name)
    : spec_sel (spec_sel), ret_type (ret_type), param_set (param_set), vararg (vararg), cv (cv), throw_spec (throw_spec), name (name)
         {}
}
namespace
{
  InstantiateFunc::~ InstantiateFunc ()
         {}
}
namespace smtc
{
  void instantiateFunc (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, NamePtr const & name)
  {
    scope->accept (InstantiateFunc (spec_sel, ret_type, param_set, vararg, cv, throw_spec, name));
  }
}
#undef LZZ_INLINE
