// smtc_CreateLinkageSpecScope.h
//

#ifndef LZZ_smtc_CreateLinkageSpecScope_h
#define LZZ_smtc_CreateLinkageSpecScope_h
// semantic
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace util
{
  class Ident;
}
namespace util
{
  class Loc;
}
namespace smtc
{
  class Linkage;
}
namespace smtc
{
  ScopePtr createLinkageSpecScope (ScopePtr const & parent, util::Loc const & loc, Linkage const & linkage);
}
#undef LZZ_INLINE
#endif
