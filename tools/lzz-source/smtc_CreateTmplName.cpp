// smtc_CreateTmplName.cpp
//

#include "smtc_CreateTmplName.h"
// semantic
#include "smtc_TmplName.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr createTmplName (BaseNamePtr const & base_name, bool has_tmpl, gram::Block const & args)
  {
    args.trim ();
    return createTmplName (base_name, has_tmpl, args.toString ());
  }
}
namespace smtc
{
  NamePtr createTmplName (BaseNamePtr const & base_name, bool has_tmpl, util::String const & args)
  {
    return new TmplName (base_name, has_tmpl, args);
  }
}
#undef LZZ_INLINE
