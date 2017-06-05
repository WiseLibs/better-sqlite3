// smtc_ThrowSpec.cpp
//

#include "smtc_ThrowSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  ThrowSpec::ThrowSpec (CvTypeVector const & cv_type_set)
    : m_cv_type_set (cv_type_set)
    {}
}
namespace smtc
{
  ThrowSpec::~ ThrowSpec ()
    {}
}
namespace smtc
{
  CvTypeVector const & ThrowSpec::getCvTypeSet () const
    {
      return m_cv_type_set;
    }
}
#undef LZZ_INLINE
