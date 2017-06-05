// smtc_Linkage.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE Linkage::Linkage (util::Ident const & lang)
    : m_lang (lang)
    {}
}
namespace smtc
{
  LZZ_INLINE bool Linkage::isSet () const
    {
      return m_lang.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE util::Ident const & Linkage::getLanguage () const
    {
      return m_lang;
    }
}
#undef LZZ_INLINE
