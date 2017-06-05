// smtc_ClassDecl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE ClassKey ClassDecl::getKey () const
    {
      return m_key;
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & ClassDecl::getName () const
    {
      return m_name;
    }
}
#undef LZZ_INLINE
