// smtc_ParamDecl.cpp
//

#include "smtc_ParamDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamDecl::ParamDecl (NamePtr const & name)
    : m_name (name)
    {}
}
namespace smtc
{
  ParamDecl::~ ParamDecl ()
    {}
}
namespace smtc
{
  NamePtr const & ParamDecl::getName () const
    {
      return m_name;
    }
}
#undef LZZ_INLINE
