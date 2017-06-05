// smtc_TmplClassDecl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplSpecPtrVector const & TmplClassDecl::getTmplSpecSet () const
    {
      return m_tmpl_spec_set;
    }
}
namespace smtc
{
  LZZ_INLINE ClassDeclPtr const & TmplClassDecl::getClassDecl () const
    {
      return m_class_decl;
    }
}
#undef LZZ_INLINE
