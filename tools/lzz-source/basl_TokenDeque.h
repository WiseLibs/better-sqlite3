// basl_TokenDeque.h
//

#ifndef LZZ_basl_TokenDeque_h
#define LZZ_basl_TokenDeque_h
// std lib
#include <deque>

// basl
#include "basl_Token.h"
#define LZZ_INLINE inline
namespace basl
{
  typedef std::deque <Token> TokenDeque;
}
namespace basl
{
  typedef std::deque <Token>::iterator TokenDequeIter;
}
namespace basl
{
  typedef std::deque <Token>::const_iterator TokenDequeConstIter;
}
namespace basl
{
  typedef std::deque <Token>::reverse_iterator TokenDequeRevIter;
}
namespace basl
{
  typedef std::deque <Token>::const_reverse_iterator TokenDequeConstRevIter;
}
#undef LZZ_INLINE
#endif
