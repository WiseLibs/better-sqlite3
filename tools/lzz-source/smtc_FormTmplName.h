// smtc_FormTmplName.h
//

#ifndef LZZ_smtc_FormTmplName_h
#define LZZ_smtc_FormTmplName_h
// semantic
#include "smtc_NamePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr formTmplName (NamePtr const & name, util::String const & args);
}
#undef LZZ_INLINE
#endif
