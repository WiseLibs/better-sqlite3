// smtc_Obj.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE bool Obj::hasLinkage () const
    {
      return m_linkage.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE Linkage const & Obj::getLinkage () const
    {
      return m_linkage;
    }
}
namespace smtc
{
  LZZ_INLINE int Obj::getFlags () const
    {
      return m_flags;
    }
}
namespace smtc
{
  LZZ_INLINE CvType const & Obj::getCvType () const
    {
      return m_cv_type;
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & Obj::getName () const
    {
      return m_name;
    }
}
namespace smtc
{
  LZZ_INLINE InitPtr const & Obj::getInit () const
    {
      return m_init;
    }
}
#undef LZZ_INLINE
