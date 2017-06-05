// smtc_TypeParam.h
//

#ifndef LZZ_smtc_TypeParam_h
#define LZZ_smtc_TypeParam_h
// semantic
#include "smtc_CvType.h"
#include "smtc_Param.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TypeParam : public Param
  {
    CvType m_def_type;
  public:
    TypeParam (NamePtr const & name, CvType const & def_type);
    ~ TypeParam ();
    bool hasDefaultType () const;
    CvType const & getDefaultType () const;
    util::String toString (bool is_decl) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TypeParam.inl"
#endif
#endif
