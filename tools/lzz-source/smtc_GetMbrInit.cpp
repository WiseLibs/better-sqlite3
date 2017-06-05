// smtc_GetMbrInit.cpp
//

#include "smtc_GetMbrInit.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_CreateMbrInit.h"
#define LZZ_INLINE inline
namespace smtc
{
  MbrInitPtr getMbrInit (NamePtr const & name, gram::BlockVector const & arg_set)
  {
    std::for_each (arg_set.begin (), arg_set.end (), gram::TrimBlock ());
    return createMbrInit (name, arg_set);
  }
}
#undef LZZ_INLINE
