// util_BitOp.h
//

#ifndef LZZ_util_BitOp_h
#define LZZ_util_BitOp_h
#define LZZ_INLINE inline
namespace util
{
  template <typename T>
  void setBit (T & t, int b);
}
namespace util
{
  template <typename T>
  bool isBitSet (T const & t, int b);
}
namespace util
{
  template <typename T>
  bool isBitsSet (T const & t, int b);
}
namespace util
{
  template <typename T>
  void setFlag (T & t, int b);
}
namespace util
{
  template <typename T>
  bool hasFlag (T const & t, int b);
}
namespace util
{
  template <typename T>
  bool hasFlags (T const & t, int b);
}
namespace util
{
  template <typename T>
  void clearBit (T & t, int b);
}
namespace util
{
  template <typename T>
  void clrFlag (T & t, int b);
}
namespace util
{
  template <typename T>
  LZZ_INLINE void setBit (T & t, int b)
  {
    t |= b;
  }
}
namespace util
{
  template <typename T>
  LZZ_INLINE bool isBitSet (T const & t, int b)
  {
    return (t & b) != 0;
  }
}
namespace util
{
  template <typename T>
  LZZ_INLINE bool isBitsSet (T const & t, int b)
  {
    return (t & b) == b;
  }
}
namespace util
{
  template <typename T>
  LZZ_INLINE void setFlag (T & t, int b)
  {
    t |= b;
  }
}
namespace util
{
  template <typename T>
  LZZ_INLINE bool hasFlag (T const & t, int b)
  {
    return (t & b) != 0;
  }
}
namespace util
{
  template <typename T>
  LZZ_INLINE bool hasFlags (T const & t, int b)
  {
    return (t & b) == b;
  }
}
namespace util
{
  template <typename T>
  LZZ_INLINE void clearBit (T & t, int b)
  {
    t &= ~ b;
  }
}
namespace util
{
  template <typename T>
  LZZ_INLINE void clrFlag (T & t, int b)
  {
    t &= ~ b;
  }
}
#undef LZZ_INLINE
#endif
