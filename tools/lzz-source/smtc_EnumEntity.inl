// smtc_EnumEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE EnumPtr const & EnumEntity::getEnum () const
    {
      return m_en;
    }
}
#undef LZZ_INLINE
