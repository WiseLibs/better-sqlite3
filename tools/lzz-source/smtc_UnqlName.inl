// smtc_UnqlName.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE BaseNamePtr const & UnqlName::getBaseName () const
    {
      return m_base_name;
    }
}
#undef LZZ_INLINE
