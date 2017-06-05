// smtc_MbrPtrType.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NamePtr const & MbrPtrType::getMbrName () const
    {
      return m_mbr_name;
    }
}
namespace smtc
{
  LZZ_INLINE CvType const & MbrPtrType::getToCvType () const
    {
      return m_to_cv_type;
    }
}
#undef LZZ_INLINE
