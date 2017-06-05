// smtc_LazyClassEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE LazyClassEntity::LazyClassEntity (LazyClassPtr const & lazy_ctor)
    : ClassDefnEntity (lazy_ctor)
    {}
}
#undef LZZ_INLINE
