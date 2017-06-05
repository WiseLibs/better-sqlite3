// smtc_TmplName.cpp
//

#include "smtc_TmplName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplName.inl"
#endif
// semantic
#include "smtc_NameVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplName::TmplName (BaseNamePtr const & base_name, bool has_tmpl, util::String const & args)
    : UnqlName (base_name), m_has_tmpl (has_tmpl), m_args (args)
    {}
}
namespace smtc
{
  TmplName::~ TmplName ()
    {}
}
namespace smtc
{
  util::String const & TmplName::getArgs () const
    {
      return m_args;
    }
}
namespace smtc
{
  void TmplName::accept (NameVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
