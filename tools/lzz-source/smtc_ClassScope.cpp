// smtc_ClassScope.cpp
//

#include "smtc_ClassScope.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ClassScope.inl"
#endif
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  ClassScope::ClassScope (ClassDefnPtr const & class_defn)
    : m_class_defn (class_defn)
    {}
}
namespace smtc
{
  ClassScope::~ ClassScope ()
    {}
}
namespace smtc
{
  void ClassScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
