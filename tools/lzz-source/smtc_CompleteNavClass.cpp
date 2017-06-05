// smtc_CompleteNavClass.cpp
//

#include "smtc_CompleteNavClass.h"
// semantic
#include "smtc_CompleteLazyClass.h"
#include "smtc_CreateIdentBaseName.h"
#include "smtc_CreateNavSubmitFuncDefn.h"
#include "smtc_CreateNavSubmitFuncDefnEntity.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateNonTypeParam.h"
#include "smtc_GetCvTypeAsRef.h"
#include "smtc_GetNameLoc.h"
#include "smtc_GetUnqlNamePart.h"
#include "smtc_NavClass.h" 
#include "smtc_SpecFlags.h"

// util
#include "util_GetIdent.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  void defineNavClassSubmit (NavClassPtr const & nav_class);
}
namespace
{
  void defineNavClassSubmit (NavClassPtr const & nav_class)
  {
    int flags = STATIC_SPEC;
    CvType const & ret_type = nav_class->getReturnType ();
    // form param set, first param is node as reference
    ParamPtrVector param_set;
    util::Ident node_ident = util::getIdent ("node");
    NamePtr node_name = createNonTmplName (createIdentBaseName (util::Loc (), node_ident));
    CvType node_ref_type = getCvTypeAsRef (nav_class->getNodeType ());
    param_set.push_back (createNonTypeParam (0, node_ref_type, node_name, gram::Block ()));
    ParamPtrVector const & param_set_rest = nav_class->getSubmitParamSet ();
    param_set.insert (param_set.end (), param_set_rest.begin (), param_set_rest.end ());
    // submit name, use location of nav_class
    util::Ident submit_ident = util::getIdent ("submit");
    util::Loc class_loc = getNameLoc (nav_class->getName ());
    NamePtr submit_name = createNonTmplName (createIdentBaseName (class_loc, submit_ident));
    // create nav submit func defn
    NamePtr nav_name = getUnqlNamePart (nav_class->getName ());
    ObjPtrVector const & submit_obj_set = nav_class->getSubmitObjSet ();
    gram::Block const & ret_stmt = nav_class->getReturnStmt ();
    NavSubmitFuncDefnPtr func_defn = createNavSubmitFuncDefn (flags, ret_type, submit_name, param_set, nav_name, submit_obj_set, ret_stmt);
    nav_class->addEntity (createNavSubmitFuncDefnEntity (func_defn));
  }
}
namespace smtc
{
  void completeNavClass (NavClassPtr const & nav_class)
  {
    // ctor and dtor
    completeLazyClass (nav_class);
    // submit
    defineNavClassSubmit (nav_class);
  }
}
#undef LZZ_INLINE
