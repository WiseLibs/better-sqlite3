// smtc_LazyClass.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE ParamPtrVector const & LazyClass::getParamSet () const
    {
      return m_param_set;
    }
}
namespace smtc
{
  LZZ_INLINE bool LazyClass::hasVarArg () const
    {
      return m_vararg;
    }
}
namespace smtc
{
  LZZ_INLINE MbrInitPtrVector const & LazyClass::getMbrInitSet () const
    {
      return m_mbr_init_set;
    }
}
#undef LZZ_INLINE
