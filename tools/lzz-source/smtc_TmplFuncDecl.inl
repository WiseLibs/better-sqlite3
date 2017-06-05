// smtc_TmplFuncDecl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplSpecPtrVector const & TmplFuncDecl::getTmplSpecSet () const
    {
      return m_tmpl_spec_set;
    }
}
namespace smtc
{
  LZZ_INLINE FuncDeclPtr const & TmplFuncDecl::getFuncDecl () const
    {
      return m_func_decl;
    }
}
#undef LZZ_INLINE
