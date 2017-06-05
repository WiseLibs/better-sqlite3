// util_BlockImpl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace util
{
  LZZ_INLINE Loc const & BlockImpl::getLoc () const
    {
      return m_loc;
    }
}
namespace util
{
  LZZ_INLINE char const * BlockImpl::c_str () const
    {
      return m_data;
    }
}
namespace util
{
  LZZ_INLINE int BlockImpl::getNumLines () const
    {
      return m_num_lines;
    }
}
namespace util
{
  LZZ_INLINE int BlockImpl::getLength () const
    {
      return m_length;
    }
}
#undef LZZ_INLINE
