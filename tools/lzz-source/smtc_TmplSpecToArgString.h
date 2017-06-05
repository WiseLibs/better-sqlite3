// smtc_TmplSpecToArgString.h
//

#ifndef LZZ_smtc_TmplSpecToArgString_h
#define LZZ_smtc_TmplSpecToArgString_h
// semantic
#include "smtc_TmplSpecPtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String tmplSpecToArgString (TmplSpecPtr const & tmpl_spec);
}
#undef LZZ_INLINE
#endif
