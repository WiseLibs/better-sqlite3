// smtc_ParamToNavCtorParam.cpp
//

#include "smtc_ParamToNavCtorParam.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ParamToNavCtorParam.inl"
#endif
// semantic
#include "smtc_CreateNonTypeParam.h"
#include "smtc_GetCvTypeAsRef.h"
#include "smtc_NonTypeParam.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr paramToNavCtorParam (ParamPtr const & param)
  {
    NonTypeParam const & non_type_param = static_cast <NonTypeParam const &> (* param);
    CvType const & cv_type = non_type_param.getCvType ();
    return createNonTypeParam (0, getCvTypeAsRef (cv_type), non_type_param.getName (), gram::Block ());
  }
}
namespace smtc
{
  ParamToNavCtorParam::~ ParamToNavCtorParam ()
                  {}
}
#undef LZZ_INLINE
