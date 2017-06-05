// smtc_TdefEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TdefPtr const & TdefEntity::getTdef () const
    {
      return m_tdef;
    }
}
#undef LZZ_INLINE
