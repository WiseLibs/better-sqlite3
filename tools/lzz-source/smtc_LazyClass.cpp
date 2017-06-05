// smtc_LazyClass.cpp
//

#include "smtc_LazyClass.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_LazyClass.inl"
#endif
#include "smtc_BuildLazyClassMbrInitSet.h"
#define LZZ_INLINE inline
namespace smtc
{
  LazyClass::LazyClass (int flags, ClassKey key, NamePtr const & name, bool is_dll_api, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set)
    : ClassDefn (key, name, is_dll_api, base_spec_set), m_flags (flags), m_param_set (param_set), m_vararg (vararg), m_vdtor (false)
    {
      // build mbr init set
      buildLazyClassMbrInitSet (base_spec_set, m_mbr_init_set);
    }
}
namespace smtc
{
  void LazyClass::addParam (ParamPtr const & param)
    {
      m_param_set.push_back (param);
    }
}
namespace smtc
{
  void LazyClass::addMbrInit (MbrInitPtr const & mbr_init)
    {
      m_mbr_init_set.push_back (mbr_init);
    }
}
namespace smtc
{
  void LazyClass::setVirtualDtor ()
    {
      m_vdtor = true;
    }
}
namespace smtc
{
  bool LazyClass::hasVirtualDtor () const
    {
      return m_vdtor;
    }
}
#undef LZZ_INLINE
