// smtc_NavClassEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NavClassEntity::NavClassEntity (NavClassPtr const & nav_class)
    : ClassDefnEntity (nav_class)
    {}
}
#undef LZZ_INLINE
