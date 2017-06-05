// smtc_TmplName.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE bool TmplName::hasTemplateKeyword () const
    {
      return m_has_tmpl;
    }
}
#undef LZZ_INLINE
