// smtc_CvType.h
//

#ifndef LZZ_smtc_CvType_h
#define LZZ_smtc_CvType_h
// semantic
#include "smtc_Cv.h"
#include "smtc_TypePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class CvType
  {
    TypePtr m_type;
    Cv m_cv;
  public:
    explicit CvType ();
    explicit CvType (TypePtr const & type, Cv const & cv = Cv ());
    ~ CvType ();
    bool isSet () const;
    TypePtr const & getType () const;
    Cv const & getCv () const;
    util::String toString () const;
    util::String toString (util::String const & dcl, bool c = false, bool v = false) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_CvType.inl"
#endif
#endif
