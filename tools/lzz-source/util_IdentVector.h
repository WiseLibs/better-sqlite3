// util_IdentVector.h
//

#ifndef LZZ_util_IdentVector_h
#define LZZ_util_IdentVector_h
#include <vector>
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace util
{
  typedef std::vector <Ident> IdentVector;
}
namespace util
{
  typedef std::vector <Ident>::iterator IdentVectorIter;
}
namespace util
{
  typedef std::vector <Ident>::const_iterator IdentVectorConstIter;
}
#undef LZZ_INLINE
#endif
