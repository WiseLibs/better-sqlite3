// smtc_VdfDataFuncDefn.cpp
//

#include "smtc_VdfDataFuncDefn.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_VdfDataFuncDefn.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  VdfDataFuncDefn::~ VdfDataFuncDefn ()
    {}
}
namespace smtc
{
  util::String const & VdfDataFuncDefn::getComment () const
    {
      return m_cmt;
    }
}
namespace smtc
{
  void VdfDataFuncDefn::addObj (ObjPtr const & obj)
    {
      m_obj_set.push_back (obj);
    }
}
#undef LZZ_INLINE
