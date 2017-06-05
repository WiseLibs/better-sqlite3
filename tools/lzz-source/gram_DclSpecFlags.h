// gram_DclSpecFlags.h
//

#ifndef LZZ_gram_DclSpecFlags_h
#define LZZ_gram_DclSpecFlags_h
#define LZZ_INLINE inline
namespace gram
{
  enum
  {
    INLINE_SPEC = 1 << 0,
    VIRTUAL_SPEC = 1 << 1,
    EXPLICIT_SPEC = 1 << 2,
    STATIC_SPEC = 1 << 3,
    EXTERN_SPEC = 1 << 4,
    MUTABLE_SPEC = 1 << 5,
    AUTO_SPEC = 1 << 6,
    REGISTER_SPEC = 1 << 7,
    PURE_SPEC = 1 << 8,
    DLL_API_SPEC = 1 << 9
  };
}
#undef LZZ_INLINE
#endif
