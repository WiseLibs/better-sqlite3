// smtc_ThrowSpec.h
//

#ifndef LZZ_smtc_ThrowSpec_h
#define LZZ_smtc_ThrowSpec_h
// semantic
#include "smtc_CvTypeVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ThrowSpec
  {
    CvTypeVector m_cv_type_set;
  public:
    ThrowSpec (CvTypeVector const & cv_type_set);
    ~ ThrowSpec ();
    CvTypeVector const & getCvTypeSet () const;
  };
}
#undef LZZ_INLINE
#endif
