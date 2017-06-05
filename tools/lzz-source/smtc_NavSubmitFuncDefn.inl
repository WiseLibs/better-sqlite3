// smtc_NavSubmitFuncDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NavSubmitFuncDefn::NavSubmitFuncDefn (int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & nav_name, ObjPtrVector const & obj_set, gram::Block const & ret_stmt)
    : FuncDecl (Linkage (), flags, ret_type, name, param_set, false, Cv (), ThrowSpecPtr ()), m_nav_name (nav_name), m_obj_set (obj_set), m_ret_stmt (ret_stmt)
    {}
}
namespace smtc
{
  LZZ_INLINE NamePtr const & NavSubmitFuncDefn::getNavName () const
    {
      return m_nav_name;
    }
}
namespace smtc
{
  LZZ_INLINE ObjPtrVector const & NavSubmitFuncDefn::getObjSet () const
    {
      return m_obj_set;
    }
}
#undef LZZ_INLINE
