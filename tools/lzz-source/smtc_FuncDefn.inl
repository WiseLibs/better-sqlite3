// smtc_FuncDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE FuncDefn::FuncDefn (Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block)
    : FuncDecl (linkage, flags, ret_type, name, param_set, vararg, cv, throw_spec), m_ctor_init (ctor_init), m_body (body), m_try_block (try_block)
    {}
}
namespace smtc
{
  LZZ_INLINE CtorInitPtr const & FuncDefn::getCtorInit () const
    {
      return m_ctor_init;
    }
}
namespace smtc
{
  LZZ_INLINE gram::Block const & FuncDefn::getBody () const
    {
      return m_body;
    }
}
namespace smtc
{
  LZZ_INLINE TryBlockPtr const & FuncDefn::getTryBlock () const
    {
      return m_try_block;
    }
}
#undef LZZ_INLINE
