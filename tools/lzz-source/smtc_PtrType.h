// smtc_PtrType.h
//

#ifndef LZZ_smtc_PtrType_h
#define LZZ_smtc_PtrType_h
// semantic
#include "smtc_CvType.h"
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  class PtrType : public Type
  {
    CvType m_to_cv_type;
  public:
    PtrType (CvType const & to_cv_type);
    ~ PtrType ();
    TypeKind getKind () const;
    util::String toString (util::String const & dcl, bool c, bool v) const;
    CvType const & getToCvType () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PtrType.inl"
#endif
#endif
