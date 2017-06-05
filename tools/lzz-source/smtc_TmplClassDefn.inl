// smtc_TmplClassDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplClassDefn::TmplClassDefn (TmplSpecPtrVector const & tmpl_spec_set, ClassDefnPtr const & class_defn)
    : TmplClassDecl (tmpl_spec_set, class_defn)
    {}
}
namespace smtc
{
  LZZ_INLINE ClassDefnPtr TmplClassDefn::getClassDefn () const
    {
      return getClassDecl ();
    }
}
#undef LZZ_INLINE
