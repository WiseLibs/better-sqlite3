// smtc_NavClass.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE CvType const & NavClass::getReturnType () const
    {
      return m_ret_type;
    }
}
namespace smtc
{
  LZZ_INLINE ParamPtrVector const & NavClass::getSubmitParamSet () const
    {
      return m_submit_param_set;
    }
}
namespace smtc
{
  LZZ_INLINE CvType const & NavClass::getNodeType () const
    {
      return m_node_type;
    }
}
namespace smtc
{
  LZZ_INLINE ObjPtrVector const & NavClass::getSubmitObjSet () const
    {
      return m_submit_obj_set;
    }
}
#undef LZZ_INLINE
