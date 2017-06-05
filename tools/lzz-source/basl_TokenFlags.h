// basl_TokenFlags.h
//

#ifndef LZZ_basl_TokenFlags_h
#define LZZ_basl_TokenFlags_h
#define LZZ_INLINE inline
namespace basl
{
  enum
  {
    IS_SET_TOKEN = 1 << 0,
    REC_SUB_MACRO_TOKEN = 1 << 1,
    SPACE_BEFORE_TOKEN = 1 << 2,
    FROM_MACRO_TOKEN = 1 << 3
  };
}
#undef LZZ_INLINE
#endif
