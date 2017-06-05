// smtc_TmplLazyClass.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplLazyClass::TmplLazyClass (TmplSpecPtrVector const & tmpl_spec_set, LazyClassPtr const & lazy_class)
    : TmplClassDefn (tmpl_spec_set, lazy_class)
    {}
}
namespace smtc
{
  LZZ_INLINE LazyClassPtr TmplLazyClass::getLazyClass () const
    {
      return getClassDecl ();
    }
}
#undef LZZ_INLINE
