// gram_IsHexDigit.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE bool isHexDigit (char ch)
  {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
  }
}
#undef LZZ_INLINE
