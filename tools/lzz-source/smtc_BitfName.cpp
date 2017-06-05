// smtc_BitfName.cpp
//

#include "smtc_BitfName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_BitfName.inl"
#endif
#include "smtc_NameVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  BitfName::BitfName (util::Loc const & loc, util::Ident const & ident, util::String const & size)
    : m_loc (loc), m_ident (ident), m_size (size)
    {}
}
namespace smtc
{
  BitfName::~ BitfName ()
    {}
}
namespace smtc
{
  void BitfName::accept (NameVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
