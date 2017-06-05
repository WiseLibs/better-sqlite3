// smtc_FuncDeclEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE FuncDeclPtr const & FuncDeclEntity::getFuncDecl () const
    {
      return m_func_decl;
    }
}
#undef LZZ_INLINE
