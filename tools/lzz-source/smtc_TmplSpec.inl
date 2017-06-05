// smtc_TmplSpec.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::Loc const & TmplSpec::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE ParamPtrVector const & TmplSpec::getParamSet () const
    {
      return m_param_set;
    }
}
#undef LZZ_INLINE
