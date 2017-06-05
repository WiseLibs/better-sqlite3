// gram_ParserData.h
//

#ifndef LZZ_gram_ParserData_h
#define LZZ_gram_ParserData_h
#define LZZ_INLINE inline
namespace basl
{
  struct LRData;
}
namespace gram
{
  basl::LRData const * getParserData ();
}
#undef LZZ_INLINE
#endif
