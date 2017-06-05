// smtc_RefType.cpp
//

#include "smtc_RefType.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_RefType.inl"
#endif
// semantic
#include "smtc_AppendCv.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  RefType::RefType (CvType const & to_cv_type)
    : m_to_cv_type (to_cv_type)
    {}
}
namespace smtc
{
  RefType::~ RefType ()
    {}
}
namespace smtc
{
  TypeKind RefType::getKind () const
    {
      return REF_TYPE;
    }
}
namespace smtc
{
  util::String RefType::toString (util::String const & dcl, bool c, bool v) const
    {
      util::String str;
      str = '&';
      util::appendWithSpace (str, dcl);
      return m_to_cv_type.toString (str);
    }
}
#undef LZZ_INLINE
