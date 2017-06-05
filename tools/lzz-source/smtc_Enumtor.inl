// smtc_Enumtor.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NamePtr const & Enumtor::getName () const
    {
      return m_name;
    }
}
namespace smtc
{
  LZZ_INLINE bool Enumtor::hasInit () const
    {
      return m_init.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE gram::Block const & Enumtor::getInit () const
    {
      return m_init;
    }
}
#undef LZZ_INLINE
