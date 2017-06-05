// smtc_TmplClassDefnEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplClassDefnEntity::TmplClassDefnEntity (TmplClassDefnPtr const & tmpl_class_defn)
    : TmplClassDeclEntity (tmpl_class_defn)
    {}
}
#undef LZZ_INLINE
