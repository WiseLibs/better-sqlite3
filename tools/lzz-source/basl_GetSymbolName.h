// basl_GetSymbolName.h
//

#ifndef LZZ_basl_GetSymbolName_h
#define LZZ_basl_GetSymbolName_h
#define LZZ_INLINE inline
namespace basl
{
  struct LRData;
}
namespace basl
{
  char const * getSymbolName (LRData const & data, int number);
}
#undef LZZ_INLINE
#endif
