// smtc_UnqlName.cpp
//

#include "smtc_UnqlName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_UnqlName.inl"
#endif
#include "smtc_BaseName.h"
#define LZZ_INLINE inline
namespace smtc
{
  UnqlName::UnqlName (BaseNamePtr const & base_name)
    : m_base_name (base_name)
    {}
}
namespace smtc
{
  UnqlName::~ UnqlName ()
    {}
}
namespace smtc
{
  util::Loc const & UnqlName::getLoc () const
    {
      return m_base_name->getLoc ();
    }
}
#undef LZZ_INLINE
