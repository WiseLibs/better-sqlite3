// smtc_FrndClassDeclEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE ClassDeclPtr const & FrndClassDeclEntity::getClassDecl () const
    {
      return m_class_decl;
    }
}
#undef LZZ_INLINE
