// smtc_MbrPtrType.h
//

#ifndef LZZ_smtc_MbrPtrType_h
#define LZZ_smtc_MbrPtrType_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  class MbrPtrType : public Type
  {
    NamePtr m_mbr_name;
    CvType m_to_cv_type;
  public:
    MbrPtrType (NamePtr const & mbr_name, CvType const & to_cv_type);
    ~ MbrPtrType ();
    TypeKind getKind () const;
    util::String toString (util::String const & dcl, bool c, bool v) const;
    NamePtr const & getMbrName () const;
    CvType const & getToCvType () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_MbrPtrType.inl"
#endif
#endif
