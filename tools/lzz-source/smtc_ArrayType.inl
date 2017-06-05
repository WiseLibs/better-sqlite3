// smtc_ArrayType.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE CvType const & ArrayType::getElementCvType () const
    {
      return m_elem_cv_type;
    }
}
namespace smtc
{
  LZZ_INLINE util::String const & ArrayType::getSize () const
    {
      return m_size;
    }
}
#undef LZZ_INLINE
