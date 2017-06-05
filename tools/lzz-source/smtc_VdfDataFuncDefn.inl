// smtc_VdfDataFuncDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE VdfDataFuncDefn::VdfDataFuncDefn (int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, util::String const & cmt)
    : FuncDecl (Linkage (), flags, ret_type, name, param_set, vararg, Cv (), ThrowSpecPtr ()), m_cmt (cmt)
    {}
}
namespace smtc
{
  LZZ_INLINE ObjPtrVector const & VdfDataFuncDefn::getObjSet () const
    {
      return m_obj_set;
    }
}
namespace smtc
{
  LZZ_INLINE bool VdfDataFuncDefn::hasReturnStmt () const
    {
      return m_ret_stmt.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE gram::Block const & VdfDataFuncDefn::getReturnStmt () const
    {
      return m_ret_stmt;
    }
}
namespace smtc
{
  LZZ_INLINE void VdfDataFuncDefn::setReturnStmt (gram::Block const & stmt)
    {
      m_ret_stmt = stmt;
    }
}
#undef LZZ_INLINE
