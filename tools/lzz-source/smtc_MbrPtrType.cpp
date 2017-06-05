// smtc_MbrPtrType.cpp
//

#include "smtc_MbrPtrType.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_MbrPtrType.inl"
#endif
// semantic
#include "smtc_AppendCv.h"
#include "smtc_NameToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  MbrPtrType::MbrPtrType (NamePtr const & mbr_name, CvType const & to_cv_type)
    : m_mbr_name (mbr_name), m_to_cv_type (to_cv_type)
    {}
}
namespace smtc
{
  MbrPtrType::~ MbrPtrType ()
    {}
}
namespace smtc
{
  TypeKind MbrPtrType::getKind () const
    {
      return MBR_PTR_TYPE;
    }
}
namespace smtc
{
  util::String MbrPtrType::toString (util::String const & dcl, bool c, bool v) const
    {
      util::String str = nameToString (m_mbr_name);
      str += "::*";
      appendCv (str, c, v);
      util::appendWithSpace (str, dcl);
      return m_to_cv_type.toString (str);
    }
}
#undef LZZ_INLINE
