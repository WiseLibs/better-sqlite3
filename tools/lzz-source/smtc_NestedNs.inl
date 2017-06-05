// smtc_NestedNs.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NsPtr const & NestedNs::getEnclNs () const
    {
      return m_encl_ns;
    }
}
namespace smtc
{
  LZZ_INLINE util::Loc const & NestedNs::getLoc () const
    {
      return m_loc;
    }
}
#undef LZZ_INLINE
