// smtc_FrndTmplClassDeclEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplClassDeclPtr const & FrndTmplClassDeclEntity::getTmplClassDecl () const
    {
      return m_tmpl_class_decl;
    }
}
#undef LZZ_INLINE
