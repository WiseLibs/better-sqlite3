// basl_TokenList.h
//

#ifndef LZZ_basl_TokenList_h
#define LZZ_basl_TokenList_h
// std lib
#include <list>

// basil
#include "basl_Token.h"
#define LZZ_INLINE inline
namespace basl
{
  typedef std::list <Token> TokenList;
}
namespace basl
{
  typedef std::list <Token>::iterator TokenListIter;
}
namespace basl
{
  typedef std::list <Token>::const_iterator TokenListConstIter;
}
#undef LZZ_INLINE
#endif
