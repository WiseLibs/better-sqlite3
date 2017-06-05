// smtc_GetFuncParam.cpp
//

#include "smtc_GetFuncParam.h"
// semantic
#include "smtc_CheckParamName.h"
#include "smtc_CheckSpecFlags.h"
#include "smtc_CreateNonTypeParam.h"
#include "smtc_Message.h"
#include "smtc_SpecFlags.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr getFuncParam (gram::SpecSel const & spec_sel, CvType const & cv_type, NamePtr const & name, gram::Block const & def_arg)
  {
    // only auto and register valid
    checkValidSpecFlags (spec_sel, AUTO_SPEC|REGISTER_SPEC, msg::invalidFuncParamSpec);

    // check name
    checkParamName (name);

    // return non-type param
    int flags = spec_sel.getFlags ();
    return createNonTypeParam (flags, cv_type, name, def_arg);
  }
}
#undef LZZ_INLINE
