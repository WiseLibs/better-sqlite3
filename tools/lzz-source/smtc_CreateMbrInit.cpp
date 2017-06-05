// smtc_CreateMbrInit.cpp
//

#include "smtc_CreateMbrInit.h"
// semantic
#include "smtc_ArgListToString.h"
#include "smtc_MbrInit.h"
#define LZZ_INLINE inline
namespace smtc
{
  MbrInitPtr createMbrInit (NamePtr const & name, util::String const & arg_set)
  {
    return new MbrInit (name, arg_set);
  }
}
namespace smtc
{
  MbrInitPtr createMbrInit (NamePtr const & name, gram::BlockVector const & arg_set)
  {
    return createMbrInit (name, argListToString (arg_set));
  }
}
#undef LZZ_INLINE
