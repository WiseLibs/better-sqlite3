// smtc_NavClass.cpp
//

#include "smtc_NavClass.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NavClass.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  NavClass::NavClass (int flags, NamePtr const & name, ParamPtrVector const & ctor_param_set, BaseSpecPtrVector const & base_spec_set, CvType const & ret_type, CvType const & node_type, ParamPtrVector const & submit_param_set)
    : LazyClass (flags, STRUCT_KEY, name, false, ctor_param_set, false, base_spec_set), m_ret_type (ret_type), m_node_type (node_type), m_submit_param_set (submit_param_set)
    {}
}
namespace smtc
{
  void NavClass::addSubmitObj (ObjPtr const & obj)
    {
      m_submit_obj_set.push_back (obj);
    }
}
namespace smtc
{
  bool NavClass::hasReturnStmt () const
    {
      return m_return_stmt.isSet ();
    }
}
namespace smtc
{
  void NavClass::setReturnStmt (gram::Block const & stmt)
    {
      m_return_stmt = stmt;
    }
}
namespace smtc
{
  gram::Block const & NavClass::getReturnStmt () const
    {
      return m_return_stmt;
    }
}
#undef LZZ_INLINE
