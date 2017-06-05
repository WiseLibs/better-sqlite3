// smtc_TypeParam.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE bool TypeParam::hasDefaultType () const
    {
      return m_def_type.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE CvType const & TypeParam::getDefaultType () const
    {
      return m_def_type;
    }
}
#undef LZZ_INLINE
