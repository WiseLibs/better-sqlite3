// smtc_VdfScope.cpp
//

#include "smtc_VdfScope.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_VdfScope.inl"
#endif
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  VdfScope::VdfScope (NsPtr const & outer_ns, NamePtr const & base_type_name, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, ThrowSpecPtr const & throw_spec, NsPtr const & private_ns)
    : m_outer_ns (outer_ns), m_base_type_name (base_type_name), m_ret_type (ret_type), m_name (name), m_param_set (param_set), m_vararg (vararg), m_throw_spec (throw_spec), m_private_ns (private_ns)
    {}
}
namespace smtc
{
  VdfScope::~ VdfScope ()
    {}
}
namespace smtc
{
  void VdfScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
