// util_Ident.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace util
{
  LZZ_INLINE Ident::Ident ()
    : m_key (0)
    {}
}
namespace util
{
  LZZ_INLINE Ident::Ident (char const * key)
    : m_key (key)
    {}
}
namespace util
{
  LZZ_INLINE bool Ident::isSet () const
    {
      return m_key != 0;
    }
}
namespace util
{
  LZZ_INLINE char const * Ident::c_str () const
    {
      return m_key;
    }
}
namespace util
{
  LZZ_INLINE size_t Ident::getHandle () const
    {
      return (size_t) m_key;
    }
}
namespace util
{
  LZZ_INLINE bool operator == (Ident const & a, Ident const & b)
  {
    return a.c_str () == b.c_str ();
  }
}
namespace util
{
  LZZ_INLINE bool operator != (Ident const & a, Ident const & b)
  {
    return ! (a == b);
  }
}
#undef LZZ_INLINE
