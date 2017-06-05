// basl_TokenVector.h
//

#ifndef LZZ_basl_TokenVector_h
#define LZZ_basl_TokenVector_h
// std lib
#include <vector>

// basl
#include "basl_Token.h"
#define LZZ_INLINE inline
namespace basl
{
  typedef std::vector <Token> TokenVector;
}
namespace basl
{
  typedef std::vector <Token>::iterator TokenVectorIter;
}
namespace basl
{
  typedef std::vector <Token>::const_iterator TokenVectorConstIter;
}
namespace basl
{
  typedef std::vector <Token>::reverse_iterator TokenVectorRevIter;
}
namespace basl
{
  typedef std::vector <Token>::const_reverse_iterator TokenVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
