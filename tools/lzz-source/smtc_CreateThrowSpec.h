// smtc_CreateThrowSpec.h
//

#ifndef LZZ_smtc_CreateThrowSpec_h
#define LZZ_smtc_CreateThrowSpec_h
// semantic
#include "smtc_CvTypeVector.h"
#include "smtc_ThrowSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ThrowSpecPtr createThrowSpec (CvTypeVector const & cv_type_set);
}
#undef LZZ_INLINE
#endif
