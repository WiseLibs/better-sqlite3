// smtc_TmplParam.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE ParamPtrVector const & TmplParam::getParamSet () const
    {
      return m_param_set;
    }
}
namespace smtc
{
  LZZ_INLINE bool TmplParam::hasDefaultName () const
    {
      return m_def_name.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & TmplParam::getDefaultName () const
    {
      return m_def_name;
    }
}
#undef LZZ_INLINE
