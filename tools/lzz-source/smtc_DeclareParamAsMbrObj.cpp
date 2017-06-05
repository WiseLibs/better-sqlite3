// smtc_DeclareParamAsMbrObj.cpp
//

#include "smtc_DeclareParamAsMbrObj.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_DeclareParamAsMbrObj.inl"
#endif
// semantic
#include "smtc_CreateMbrInit.h"
#include "smtc_CreateObj.h"
#include "smtc_CreateObjEntity.h"
#include "smtc_GetCvTypeAsRef.h"
#include "smtc_LazyClass.h"
#include "smtc_NameToString.h"
#include "smtc_NonTypeParam.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareParamAsMbrObj (LazyClassPtr const & lazy_class, ParamPtr const & param, bool as_ref)
  {
    // create obj, param is a non-type param
    NonTypeParam const & non_type_param = static_cast <NonTypeParam const &> (* param);
    NamePtr const & name = non_type_param.getName ();
    CvType param_type = non_type_param.getCvType ();
    if (as_ref)
    {
      param_type = getCvTypeAsRef (param_type);
    }
    ObjPtr obj = createObj (0, param_type, name, InitPtr ());
    lazy_class->addEntity (createObjEntity (obj));
    // add member init
    lazy_class->addMbrInit (createMbrInit (name, nameToString (name)));
  }
}
namespace smtc
{
  DeclareParamAsMbrObj::~ DeclareParamAsMbrObj ()
              {}
}
#undef LZZ_INLINE
