// smtc_VdfScope.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NsPtr const & VdfScope::getOuterNs () const
    {
      return m_outer_ns;
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & VdfScope::getBaseTypeName () const
    {
      return m_base_type_name;
    }
}
namespace smtc
{
  LZZ_INLINE CvType const & VdfScope::getReturnType () const
    {
      return m_ret_type;
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & VdfScope::getName () const
    {
      return m_name;
    }
}
namespace smtc
{
  LZZ_INLINE ParamPtrVector const & VdfScope::getParamSet () const
    {
      return m_param_set;
    }
}
namespace smtc
{
  LZZ_INLINE bool VdfScope::hasVarArg () const
    {
      return m_vararg;
    }
}
namespace smtc
{
  LZZ_INLINE ThrowSpecPtr const & VdfScope::getThrowSpec () const
    {
      return m_throw_spec;
    }
}
namespace smtc
{
  LZZ_INLINE NsPtr const & VdfScope::getPrivateNs () const
    {
      return m_private_ns;
    }
}
#undef LZZ_INLINE
