// smtc_CreateTmplName.h
//

#ifndef LZZ_smtc_CreateTmplName_h
#define LZZ_smtc_CreateTmplName_h
// semantic
#include "smtc_BaseNamePtr.h"
#include "smtc_NamePtr.h"

// gram
#include "gram_Block.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr createTmplName (BaseNamePtr const & base_name, bool has_tmpl, gram::Block const & args);
}
namespace smtc
{
  NamePtr createTmplName (BaseNamePtr const & base_name, bool has_tmpl, util::String const & args);
}
#undef LZZ_INLINE
#endif
