// smtc_ArrayType.cpp
//

#include "smtc_ArrayType.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ArrayType.inl"
#endif
// semantic
#include "smtc_AppendCv.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  ArrayType::ArrayType (CvType const & elem_cv_type, util::String const & size)
    : m_elem_cv_type (elem_cv_type), m_size (size)
    {}
}
namespace smtc
{
  ArrayType::~ ArrayType ()
    {}
}
namespace smtc
{
  TypeKind ArrayType::getKind () const
    {
      return ARRAY_TYPE;
    }
}
namespace smtc
{
  util::String ArrayType::toString (util::String const & dcl, bool c, bool v) const
    {
      util::String str;
      if (! dcl.empty ())
      {
        str += '(';
        str += dcl;
        str += ')';
      }
      util::appendWithSpace (str, '[');
      str += m_size;
      str += ']';
      return m_elem_cv_type.toString (str);
    }
}
#undef LZZ_INLINE
