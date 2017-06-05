// smtc_BitfName.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::Loc const & BitfName::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE bool BitfName::hasIdent () const
    {
      return m_ident;
    }
}
namespace smtc
{
  LZZ_INLINE util::Ident const & BitfName::getIdent () const
    {
      return m_ident;
    }
}
namespace smtc
{
  LZZ_INLINE util::String const & BitfName::getSize () const
    {
      return m_size;
    }
}
#undef LZZ_INLINE
