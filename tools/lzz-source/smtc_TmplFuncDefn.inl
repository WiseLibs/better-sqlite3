// smtc_TmplFuncDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplFuncDefn::TmplFuncDefn (TmplSpecPtrVector const & tmpl_spec_set, FuncDefnPtr const & func_defn)
    : TmplFuncDecl (tmpl_spec_set, func_defn)
    {}
}
namespace smtc
{
  LZZ_INLINE FuncDefnPtr TmplFuncDefn::getFuncDefn () const
    {
      return getFuncDecl ();
    }
}
#undef LZZ_INLINE
