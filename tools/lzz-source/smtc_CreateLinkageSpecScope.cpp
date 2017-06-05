// smtc_CreateLinkageSpecScope.cpp
//

#include "smtc_CreateLinkageSpecScope.h"
// semantic
#include "smtc_LinkageSpecScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createLinkageSpecScope (ScopePtr const & parent, util::Loc const & loc, Linkage const & linkage)
  {
    return new LinkageSpecScope (parent, loc, linkage);
  }
}
#undef LZZ_INLINE
