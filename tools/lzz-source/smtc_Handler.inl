// smtc_Handler.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::Loc const & Handler::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE bool Handler::hasCatchParam () const
    {
      return m_catch_decl.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE ParamPtr const & Handler::getCatchParam () const
    {
      return m_catch_decl;
    }
}
namespace smtc
{
  LZZ_INLINE gram::Block const & Handler::getBody () const
    {
      return m_body;
    }
}
#undef LZZ_INLINE
