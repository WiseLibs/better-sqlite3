// smtc_DefineNavVisitFunc.cpp
//

#include "smtc_DefineNavVisitFunc.h"
// semantic
#include "smtc_CheckParamName.h"
#include "smtc_CreateFuncDefn.h"
#include "smtc_CreateFuncDefnEntity.h"
#include "smtc_CreateIdentBaseName.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateNonTypeParam.h"
#include "smtc_GetBuiltInType.h"
#include "smtc_GetNameLoc.h"
#include "smtc_GetRefType.h"
#include "smtc_GetUserType.h"
#include "smtc_Linkage.h"
#include "smtc_Message.h"
#include "smtc_NavClass.h"
#include "smtc_NavClassScope.h"
#include "smtc_ScopeVisitor.h"

// util
#include "util_GetIdent.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DefineNavVisitFunc : ScopeVisitor
  {
    NamePtr const & type_name;
    NamePtr const & param_name;
    gram::Block const & body;
    void visit (NavClassScope const & scope) const;
  public:
    explicit DefineNavVisitFunc (NamePtr const & type_name, NamePtr const & param_name, gram::Block const & body);
    ~ DefineNavVisitFunc ();
  };
}
namespace
{
  void DefineNavVisitFunc::visit (NavClassScope const & scope) const
    {
      // check param name
      checkParamName (param_name);
      // define func, param type is reference to type_name with node type cv
      NavClassPtr const & nav_class = scope.getNavClass ();
      CvType param_type = CvType (getUserType (type_name), nav_class->getNodeType ().getCv ());
      param_type = CvType (getRefType (param_type));
      ParamPtrVector param_set;
      param_set.push_back (createNonTypeParam (0, param_type, param_name, gram::Block ()));
      CvType ret_type = CvType (getVoidType ());
      NamePtr name = createNonTmplName (createIdentBaseName (getNameLoc (type_name), util::getIdent ("onNode")));
      Cv cv (true, false);
      FuncDefnPtr func_defn = createFuncDefn (Linkage (), 0, ret_type, name, param_set, false, cv, ThrowSpecPtr (), CtorInitPtr (),
          body, TryBlockPtr ());
      nav_class->addEntity (createFuncDefnEntity (func_defn));
    }
}
namespace
{
  LZZ_INLINE DefineNavVisitFunc::DefineNavVisitFunc (NamePtr const & type_name, NamePtr const & param_name, gram::Block const & body)
    : type_name (type_name), param_name (param_name), body (body)
         {}
}
namespace
{
  DefineNavVisitFunc::~ DefineNavVisitFunc ()
         {}
}
namespace smtc
{
  void defineNavVisitFunc (ScopePtr const & cs, NamePtr const & type_name, NamePtr const & param_name, gram::Block const & body)
  {
    cs->accept (DefineNavVisitFunc (type_name, param_name, body));
  }
}
#undef LZZ_INLINE
