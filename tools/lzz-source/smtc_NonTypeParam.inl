// smtc_NonTypeParam.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NonTypeParam::NonTypeParam (int flags, CvType const & cv_type, NamePtr const & name, gram::Block const & def_arg)
    : Param (name), m_flags (flags), m_cv_type (cv_type), m_def_arg (def_arg)
    {}
}
namespace smtc
{
  LZZ_INLINE CvType const & NonTypeParam::getCvType () const
    {
      return m_cv_type;
    }
}
namespace smtc
{
  LZZ_INLINE bool NonTypeParam::hasDefaultArg () const
    {
      return m_def_arg.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE gram::Block const & NonTypeParam::getDefaultArg () const
    {
      return m_def_arg;
    }
}
#undef LZZ_INLINE
