// basl_GetSymbolName.cpp
//

#include "basl_GetSymbolName.h"
// basil
#include "basl_LRData.h"
#define LZZ_INLINE inline
namespace basl
{
  char const * getSymbolName (LRData const & data, int number)
  {
    return data.symbol_set [number].name;
  }
}
#undef LZZ_INLINE
