// smtc_DefineNavClass.cpp
//

#include "smtc_DefineNavClass.h"
// semantic
#include "smtc_CreateNavClass.h"
#include "smtc_CreateNavClassEntity.h"
#include "smtc_CreateNavClassScope.h"
#include "smtc_DeclareLazyClassObjParamSet.h"
#include "smtc_Message.h"
#include "smtc_NavClass.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ParamToNavCtorParam.h"
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DefineNavClass : ScopeVisitor
  {
    gram::SpecSel const & spec_sel;
    CvType const & ret_type;
    NamePtr const & name;
    CvType const & node_type;
    ParamPtrVector const & param_set;
    BaseSpecPtrVector const & base_spec_set;
    ScopePtr & res_scope;
    void visit (NsScope const & scope) const;
  public:
    explicit DefineNavClass (gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, CvType const & node_type, ParamPtrVector const & param_set, BaseSpecPtrVector const & base_spec_set, ScopePtr & res_scope);
    ~ DefineNavClass ();
  };
}
namespace
{
  void DefineNavClass::visit (NsScope const & scope) const
    {
      int flags = spec_sel.getFlags ();
      ParamPtrVector ctor_param_set;
      std::transform (param_set.begin (), param_set.end (), std::back_inserter (ctor_param_set), ParamToNavCtorParam ());
      NavClassPtr nav_class = createNavClass (flags, name, ctor_param_set, base_spec_set, ret_type, node_type, param_set);
      // declare params as references 
      declareLazyClassObjParamSet (nav_class, param_set, base_spec_set, true);
      nav_class->setQualName (name);
      res_scope = createNavClassScope (nav_class);
      EntityPtr entity = createNavClassEntity (nav_class);
      scope.getNs ()->addEntity (entity);
    }
}
namespace
{
  LZZ_INLINE DefineNavClass::DefineNavClass (gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, CvType const & node_type, ParamPtrVector const & param_set, BaseSpecPtrVector const & base_spec_set, ScopePtr & res_scope)
    : spec_sel (spec_sel), ret_type (ret_type), name (name), node_type (node_type), param_set (param_set), base_spec_set (base_spec_set), res_scope (res_scope)
         {}
}
namespace
{
  DefineNavClass::~ DefineNavClass ()
         {}
}
namespace smtc
{
  ScopePtr defineNavClass (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, CvType const & node_type, ParamPtrVector const & param_set, BaseSpecPtrVector const & base_spec_set)
  {
    ScopePtr res_scope;
    scope->accept (DefineNavClass (spec_sel, ret_type, name, node_type, param_set, base_spec_set, res_scope));
    return res_scope;
  }
}
#undef LZZ_INLINE
