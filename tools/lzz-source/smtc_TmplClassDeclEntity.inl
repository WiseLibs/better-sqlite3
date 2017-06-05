// smtc_TmplClassDeclEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE TmplClassDeclPtr const & TmplClassDeclEntity::getTmplClassDecl () const
    {
      return m_tmpl_class_decl;
    }
}
#undef LZZ_INLINE
