// gram_FuncMacro.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE bool FuncMacro::hasVarArgs () const
    {
      return m_var;
    }
}
namespace gram
{
  LZZ_INLINE int FuncMacro::getNumParams () const
    {
      return m_param_set.size ();
    }
}
namespace gram
{
  LZZ_INLINE util::IdentVector const & FuncMacro::getParamSet () const
    {
      return m_param_set;
    }
}
#undef LZZ_INLINE
