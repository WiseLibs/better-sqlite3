// smtc_UsingDir.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NamePtr const & UsingDir::getName () const
    {
      return m_name;
    }
}
#undef LZZ_INLINE
