// smtc_Obj.cpp
//

#include "smtc_Obj.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_Obj.inl"
#endif
// semantic
#include "smtc_SpecFlags.h"

// util
#include "util_BitOp.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  Obj::Obj (Linkage const & linkage, int flags, CvType const & cv_type, NamePtr const & name, InitPtr const & init)
    : m_linkage (linkage), m_flags (flags), m_cv_type (cv_type), m_name (name), m_init (init)
    {}
}
namespace smtc
{
  Obj::~ Obj ()
    {}
}
namespace smtc
{
  bool Obj::isStatic () const
    {
      return hasFlag (m_flags, STATIC_SPEC);
    }
}
namespace smtc
{
  bool Obj::isExtern () const
    {
      return hasFlag (m_flags, EXTERN_SPEC);
    }
}
namespace smtc
{
  bool Obj::hasInit () const
    {
      return m_init.isSet ();
    }
}
#undef LZZ_INLINE
