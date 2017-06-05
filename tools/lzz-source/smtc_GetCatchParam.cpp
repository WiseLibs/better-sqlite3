// smtc_GetCatchParam.cpp
//

#include "smtc_GetCatchParam.h"
// semantic
#include "smtc_CheckSpecFlags.h"
#include "smtc_CreateNonTypeParam.h"
#include "smtc_Message.h"
#include "smtc_SpecFlags.h"
#define LZZ_INLINE inline
namespace smtc
{
  NonTypeParamPtr getCatchParam (gram::SpecSel const & spec_sel, CvType const & cv_type, NamePtr const & name)
  {
    // only auto and register valid
    checkValidSpecFlags (spec_sel, AUTO_SPEC|REGISTER_SPEC, msg::invalidCatchParamSpec);

    // return non-type param
    int flags = spec_sel.getFlags ();
    return createNonTypeParam (flags, cv_type, name, gram::Block ());
  }
}
#undef LZZ_INLINE
