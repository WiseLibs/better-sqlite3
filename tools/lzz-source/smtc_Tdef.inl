// smtc_Tdef.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE bool Tdef::hasLinkage () const
    {
      return m_linkage.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE Linkage const & Tdef::getLinkage () const
    {
      return m_linkage;
    }
}
namespace smtc
{
  LZZ_INLINE CvType const & Tdef::getCvType () const
    {
      return m_cv_type;
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & Tdef::getName () const
    {
      return m_name;
    }
}
#undef LZZ_INLINE
