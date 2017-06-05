// util_Ident.h
//

#ifndef LZZ_util_Ident_h
#define LZZ_util_Ident_h
// library
#include <cstddef>
#define LZZ_INLINE inline
namespace util
{
  class Ident
  {
    char const * m_key;
  public:
    Ident ();
    Ident (char const * key);
    bool isSet () const;
    char const * c_str () const;
    operator char const * () const;
    size_t getHandle () const;
  };
}
namespace util
{
  bool operator == (Ident const & a, Ident const & b);
}
namespace util
{
  bool operator != (Ident const & a, Ident const & b);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "util_Ident.inl"
#endif
#endif
