// smtc_NameVisitor.cpp
//

#include "smtc_NameVisitor.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NameVisitor.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  void NameVisitor::visit (QualName const & name) const
    {}
}
namespace smtc
{
  void NameVisitor::visit (TmplName const & name) const
    {}
}
namespace smtc
{
  void NameVisitor::visit (NonTmplName const & name) const
    {}
}
namespace smtc
{
  void NameVisitor::visit (BitfName const & name) const
    {}
}
namespace smtc
{
  NameVisitor::~ NameVisitor ()
         {}
}
#undef LZZ_INLINE
