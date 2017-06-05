// smtc_FrndTmplFuncDeclEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplFuncDeclPtr const & FrndTmplFuncDeclEntity::getTmplFuncDecl () const
    {
      return m_tmpl_func_decl;
    }
}
#undef LZZ_INLINE
