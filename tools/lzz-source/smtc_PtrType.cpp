// smtc_PtrType.cpp
//

#include "smtc_PtrType.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PtrType.inl"
#endif
// semantic
#include "smtc_AppendCv.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  PtrType::PtrType (CvType const & to_cv_type)
    : m_to_cv_type (to_cv_type)
    {}
}
namespace smtc
{
  PtrType::~ PtrType ()
    {}
}
namespace smtc
{
  TypeKind PtrType::getKind () const
    {
      return PTR_TYPE;
    }
}
namespace smtc
{
  util::String PtrType::toString (util::String const & dcl, bool c, bool v) const
    {
      util::String str;
      str = '*';
      appendCv (str, c, v);
      util::appendWithSpace (str, dcl);
      return m_to_cv_type.toString (str);
    }
}
#undef LZZ_INLINE
