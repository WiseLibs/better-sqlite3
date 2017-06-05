// smtc_BaseNameVisitor.cpp
//

#include "smtc_BaseNameVisitor.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_BaseNameVisitor.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  void BaseNameVisitor::visit (IdentBaseName const & base_name) const
    {}
}
namespace smtc
{
  void BaseNameVisitor::visit (OperBaseName const & base_name) const
    {}
}
namespace smtc
{
  void BaseNameVisitor::visit (DtorBaseName const & base_name) const
    {}
}
namespace smtc
{
  void BaseNameVisitor::visit (ConvBaseName const & base_name) const
    {}
}
namespace smtc
{
  BaseNameVisitor::~ BaseNameVisitor ()
         {}
}
#undef LZZ_INLINE
