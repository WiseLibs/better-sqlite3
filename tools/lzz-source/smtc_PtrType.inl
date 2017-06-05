// smtc_PtrType.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE CvType const & PtrType::getToCvType () const
    {
      return m_to_cv_type;
    }
}
#undef LZZ_INLINE
