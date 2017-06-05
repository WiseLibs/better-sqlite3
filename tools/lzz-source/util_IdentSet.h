// util_IdentSet.h
//

#ifndef LZZ_util_IdentSet_h
#define LZZ_util_IdentSet_h
#include <set>
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace util
{
  typedef std::set <Ident> IdentSet;
}
namespace util
{
  typedef std::set <Ident>::iterator IdentSetIter;
}
namespace util
{
  typedef std::set <Ident>::const_iterator IdentSetConstIter;
}
#undef LZZ_INLINE
#endif
