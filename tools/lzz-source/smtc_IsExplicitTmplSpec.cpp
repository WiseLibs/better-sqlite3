// smtc_IsExplicitTmplSpec.cpp
//

#include "smtc_IsExplicitTmplSpec.h"
#include <algorithm>

// semantic
#include "smtc_IsTmplSpecParamSetEmpty.h"
#include "smtc_TmplSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool isExplicitTmplSpec (TmplSpecPtrVector const & tmpl_spec_set)
  {
    return std::find_if (tmpl_spec_set.begin (), tmpl_spec_set.end (), std::not1 (IsTmplSpecParamSetEmpty ())) == tmpl_spec_set.end ();
  }
}
#undef LZZ_INLINE
