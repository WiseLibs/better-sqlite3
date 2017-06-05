// smtc_BaseSpec.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE Access BaseSpec::getAccess () const
    {
      return m_access;
    }
}
namespace smtc
{
  LZZ_INLINE bool BaseSpec::isVirtual () const
    {
      return m_is_virtual;
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & BaseSpec::getBaseName () const
    {
      return m_base_name;
    }
}
#undef LZZ_INLINE
