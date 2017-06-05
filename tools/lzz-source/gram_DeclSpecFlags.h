// gram_DeclSpecFlags.h
//

#ifndef LZZ_gram_DeclSpecFlags_h
#define LZZ_gram_DeclSpecFlags_h
#define LZZ_INLINE inline
namespace gram
{
  enum
  {
    TYPEDEF_SPEC = 1 << 0,
    FRIEND_SPEC = 1 << 1
  };
}
#undef LZZ_INLINE
#endif
