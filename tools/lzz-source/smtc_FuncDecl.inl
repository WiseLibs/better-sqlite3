// smtc_FuncDecl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE bool FuncDecl::hasLinkage () const
    {
      return m_linkage.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE Linkage const & FuncDecl::getLinkage () const
    {
      return m_linkage;
    }
}
namespace smtc
{
  LZZ_INLINE int FuncDecl::getFlags () const
    {
      return m_flags;
    }
}
namespace smtc
{
  LZZ_INLINE CvType const & FuncDecl::getReturnType () const
    {
      return m_ret_type;
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & FuncDecl::getName () const
    {
      return m_name;
    }
}
namespace smtc
{
  LZZ_INLINE ParamPtrVector const & FuncDecl::getParamSet () const
    {
      return m_param_set;
    }
}
namespace smtc
{
  LZZ_INLINE bool FuncDecl::hasVarArg () const
    {
      return m_vararg;
    }
}
namespace smtc
{
  LZZ_INLINE Cv const & FuncDecl::getCv () const
    {
      return m_cv;
    }
}
namespace smtc
{
  LZZ_INLINE ThrowSpecPtr const & FuncDecl::getThrowSpec () const
    {
      return m_throw_spec;
    }
}
namespace smtc
{
  LZZ_INLINE bool FuncDecl::hasAltReturnType () const
    {
      return m_alt_ret_type.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE CvType const & FuncDecl::getAltReturnType () const
    {
      return m_alt_ret_type;
    }
}
#undef LZZ_INLINE
