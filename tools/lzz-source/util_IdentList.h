// util_IdentList.h
//

#ifndef LZZ_util_IdentList_h
#define LZZ_util_IdentList_h
#include <list>
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace util
{
  typedef std::list <Ident> IdentList;
}
namespace util
{
  typedef std::list <Ident>::iterator IdentListIter;
}
namespace util
{
  typedef std::list <Ident>::const_iterator IdentListConstIter;
}
#undef LZZ_INLINE
#endif
