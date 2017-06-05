// smtc_Tdef.cpp
//

#include "smtc_Tdef.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_Tdef.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  Tdef::Tdef (Linkage const & linkage, CvType const & cv_type, NamePtr const & name)
    : m_linkage (linkage), m_cv_type (cv_type), m_name (name)
    {}
}
namespace smtc
{
  Tdef::~ Tdef ()
    {}
}
#undef LZZ_INLINE
