// smtc_ArrayType.h
//

#ifndef LZZ_smtc_ArrayType_h
#define LZZ_smtc_ArrayType_h
// semantic
#include "smtc_CvType.h" 
#include "smtc_Type.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ArrayType : public Type
  {
    CvType m_elem_cv_type;
    util::String m_size;
  public:
    ArrayType (CvType const & elem_cv_type, util::String const & size);
    ~ ArrayType ();
    TypeKind getKind () const;
    util::String toString (util::String const & dcl, bool c, bool v) const;
    CvType const & getElementCvType () const;
    util::String const & getSize () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ArrayType.inl"
#endif
#endif
