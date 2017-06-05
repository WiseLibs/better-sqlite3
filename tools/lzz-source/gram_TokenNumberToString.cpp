// gram_TokenNumberToString.cpp
//

#include "gram_TokenNumberToString.h"
// gram
#include "gram_ParserData.h"

// basil
#include "basl_GetSymbolName.h"
#define LZZ_INLINE inline
namespace gram
{
  char const * tokenNumberToString (int number)
  {
    return basl::getSymbolName (* getParserData (), number);
  }
}
#undef LZZ_INLINE
