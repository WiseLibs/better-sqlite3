// gram_BlockImpl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE bool BlockImpl::isTokenBlock () const
    {
      return ! isCharBlock ();
    }
}
namespace gram
{
  LZZ_INLINE util::Loc const & BlockImpl::getLoc () const
    {
      return m_loc;
    }
}
#undef LZZ_INLINE
