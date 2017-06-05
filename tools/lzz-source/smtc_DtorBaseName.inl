// smtc_DtorBaseName.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::Ident const & DtorBaseName::getIdent () const
    {
      return m_ident;
    }
}
#undef LZZ_INLINE
