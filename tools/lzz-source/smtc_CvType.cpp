// smtc_CvType.cpp
//

#include "smtc_CvType.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_CvType.inl"
#endif
// semantic
#include "smtc_Cv.h"
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType::CvType ()
    {}
}
namespace smtc
{
  CvType::CvType (TypePtr const & type, Cv const & cv)
    : m_type (type), m_cv (cv)
    {}
}
namespace smtc
{
  CvType::~ CvType ()
    {}
}
namespace smtc
{
  util::String CvType::toString (util::String const & dcl, bool c, bool v) const
    {
      return m_type->toString (dcl, c || m_cv.isConst (), v || m_cv.isVolatile ());
    }
}
#undef LZZ_INLINE
