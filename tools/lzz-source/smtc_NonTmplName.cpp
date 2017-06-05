// smtc_NonTmplName.cpp
//

#include "smtc_NonTmplName.h"
#include "smtc_NameVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  NonTmplName::NonTmplName (BaseNamePtr const & base_name)
    : UnqlName (base_name)
    {}
}
namespace smtc
{
  NonTmplName::~ NonTmplName ()
    {}
}
namespace smtc
{
  void NonTmplName::accept (NameVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
