// smtc_FrndTmplFuncDefnEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplFuncDefnPtr const & FrndTmplFuncDefnEntity::getTmplFuncDefn () const
    {
      return m_tmpl_func_defn;
    }
}
#undef LZZ_INLINE
