// smtc_FuncType.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE CvType const & FuncType::getReturnCvType () const
    {
      return m_ret_type;
    }
}
namespace smtc
{
  LZZ_INLINE CvTypeVector const & FuncType::getParamTypeSet () const
    {
      return m_param_type_set;
    }
}
namespace smtc
{
  LZZ_INLINE bool FuncType::hasVarArgs () const
    {
      return m_vararg;
    }
}
namespace smtc
{
  LZZ_INLINE Cv const & FuncType::getCv () const
    {
      return m_cv;
    }
}
namespace smtc
{
  LZZ_INLINE ThrowSpecPtr const & FuncType::getThrowSpec () const
    {
      return m_throw_spec;
    }
}
#undef LZZ_INLINE
