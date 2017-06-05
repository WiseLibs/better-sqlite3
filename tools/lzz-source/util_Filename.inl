// util_Filename.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace util
{
  LZZ_INLINE Filename::Filename ()
    : m_impl (& def_impl)
    {}
}
namespace util
{
  LZZ_INLINE bool Filename::isSet () const
    {
      return m_impl != & def_impl;
    }
}
namespace util
{
  LZZ_INLINE char const * Filename::getName () const
    {
      return m_impl->name;
    }
}
namespace util
{
  LZZ_INLINE char const * Filename::getRealName () const
    {
      return m_impl->realname;
    }
}
namespace util
{
  LZZ_INLINE bool operator != (Filename const & a, Filename const & b)
  {
    return ! (a == b);
  }
}
#undef LZZ_INLINE
