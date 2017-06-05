// smtc_Cv.h
//

#ifndef LZZ_smtc_Cv_h
#define LZZ_smtc_Cv_h
#define LZZ_INLINE inline
namespace smtc
{
  class Cv
  {
    bool m_c;
    bool m_v;
  public:
    Cv ();
    Cv (bool c, bool v);
    bool isSet () const;
    bool isConstOnly () const;
    bool isVolatileOnly () const;
    bool isConst () const;
    bool isVolatile () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Cv.inl"
#endif
#endif
