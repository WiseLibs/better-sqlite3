// smtc_UsingDeclEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE UsingDeclEntity::UsingDeclEntity (UsingDeclPtr const & using_decl)
    : m_using_decl (using_decl)
    {}
}
namespace smtc
{
  LZZ_INLINE UsingDeclPtr const & UsingDeclEntity::getUsingDecl () const
    {
      return m_using_decl;
    }
}
#undef LZZ_INLINE
