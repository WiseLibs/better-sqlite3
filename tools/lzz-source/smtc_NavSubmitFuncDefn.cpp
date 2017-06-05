// smtc_NavSubmitFuncDefn.cpp
//

#include "smtc_NavSubmitFuncDefn.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NavSubmitFuncDefn.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  NavSubmitFuncDefn::~ NavSubmitFuncDefn ()
    {}
}
namespace smtc
{
  gram::Block const & NavSubmitFuncDefn::getReturnStmt () const
    {
      return m_ret_stmt;
    }
}
#undef LZZ_INLINE
