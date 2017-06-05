// smtc_GetCvType.inl
//

// semantic
#include "smtc_GetCv.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE CvType getCvType (TypePtr const & type, bool c, bool v)
  {
    return CvType (type, getCv (c, v));
  }
}
namespace smtc
{
  LZZ_INLINE CvType getCvType (TypePtr const & type, Cv const & cv)
  {
    return CvType (type, cv);
  }
}
#undef LZZ_INLINE
