// basl_FreeTokenVector.h
//

#ifndef LZZ_basl_FreeTokenVector_h
#define LZZ_basl_FreeTokenVector_h
// std lib
#include <vector>

// basl
#include "basl_FreeToken.h"
#define LZZ_INLINE inline
namespace basl
{
  typedef std::vector <FreeToken> FreeTokenVector;
}
namespace basl
{
  typedef std::vector <FreeToken>::iterator FreeTokenIter;
}
namespace basl
{
  typedef std::vector <FreeToken>::const_iterator FreeTokenConstIter;
}
namespace basl
{
  typedef std::vector <FreeToken>::reverse_iterator FreeTokenRevIter;
}
namespace basl
{
  typedef std::vector <FreeToken>::const_reverse_iterator FreeTokenConstRevIter;
}
#undef LZZ_INLINE
#endif
