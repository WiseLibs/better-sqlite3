// smtc_GetNonTypeParam.cpp
//

#include "smtc_GetNonTypeParam.h"
// semantic
#include "smtc_CheckParamName.h"
#include "smtc_CheckSpecFlags.h"
#include "smtc_CreateNonTypeParam.h"
#include "smtc_Message.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr getNonTypeParam (gram::SpecSel const & spec_sel, CvType const & cv_type, NamePtr const & name, gram::Block const & def_arg)
  {
    // no specifiers valid
    checkValidSpecFlags (spec_sel, 0, msg::invalidNonTypeParamSpec);

    // check name
    checkParamName (name);

    // return non-type param
    return createNonTypeParam (0, cv_type, name, def_arg);
  }
}
#undef LZZ_INLINE
