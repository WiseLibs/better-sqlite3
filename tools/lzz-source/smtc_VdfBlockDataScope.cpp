// smtc_VdfBlockDataScope.cpp
//

#include "smtc_VdfBlockDataScope.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_VdfBlockDataScope.inl"
#endif
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  VdfBlockDataScope::VdfBlockDataScope (VdfDataFuncDefnPtr const & vdf_data_func_defn)
    : m_vdf_data_func_defn (vdf_data_func_defn)
    {}
}
namespace smtc
{
  VdfBlockDataScope::~ VdfBlockDataScope ()
    {}
}
namespace smtc
{
  void VdfBlockDataScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
