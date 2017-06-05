// smtc_AccessSpecEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE AccessSpecPtr const & AccessSpecEntity::getAccessSpec () const
    {
      return m_access_spec;
    }
}
#undef LZZ_INLINE
