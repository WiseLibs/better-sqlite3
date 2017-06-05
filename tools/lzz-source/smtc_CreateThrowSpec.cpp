// smtc_CreateThrowSpec.cpp
//

#include "smtc_CreateThrowSpec.h"
// semantic
#include "smtc_ThrowSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  ThrowSpecPtr createThrowSpec (CvTypeVector const & cv_type_set)
  {
    return new ThrowSpec (cv_type_set);
  }
}
#undef LZZ_INLINE
