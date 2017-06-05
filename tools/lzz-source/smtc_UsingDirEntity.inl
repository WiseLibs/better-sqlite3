// smtc_UsingDirEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE UsingDirEntity::UsingDirEntity (UsingDirPtr const & using_dir)
    : m_using_dir (using_dir)
    {}
}
namespace smtc
{
  LZZ_INLINE UsingDirPtr const & UsingDirEntity::getUsingDir () const
    {
      return m_using_dir;
    }
}
#undef LZZ_INLINE
