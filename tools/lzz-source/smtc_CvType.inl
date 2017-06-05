// smtc_CvType.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE bool CvType::isSet () const
    {
      return m_type.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE TypePtr const & CvType::getType () const
    {
      return m_type;
    }
}
namespace smtc
{
  LZZ_INLINE Cv const & CvType::getCv () const
    {
      return m_cv;
    }
}
namespace smtc
{
  LZZ_INLINE util::String CvType::toString () const
    {
      return toString (util::String (), false, false);
    }
}
#undef LZZ_INLINE
