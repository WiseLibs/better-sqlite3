// smtc_TmplLazyClassEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplLazyClassEntity::TmplLazyClassEntity (TmplLazyClassPtr const & tmpl_lazy_class)
    : TmplClassDefnEntity (tmpl_lazy_class)
    {}
}
#undef LZZ_INLINE
