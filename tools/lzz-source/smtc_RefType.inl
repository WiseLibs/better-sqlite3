// smtc_RefType.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE CvType const & RefType::getToCvType () const
    {
      return m_to_cv_type;
    }
}
#undef LZZ_INLINE
