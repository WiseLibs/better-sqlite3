// smtc_NsEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NsPtr const & NsEntity::getNs () const
    {
      return m_ns;
    }
}
#undef LZZ_INLINE
