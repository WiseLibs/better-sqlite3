// gram_CharBlockImpl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE char const * CharBlockImpl::c_str () const
    {
      return m_data;
    }
}
namespace gram
{
  LZZ_INLINE int CharBlockImpl::getNumLines () const
    {
      return m_num_lines;
    }
}
namespace gram
{
  LZZ_INLINE int CharBlockImpl::getLength () const
    {
      return m_length;
    }
}
#undef LZZ_INLINE
