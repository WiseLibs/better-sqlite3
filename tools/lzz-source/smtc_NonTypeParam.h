// smtc_NonTypeParam.h
//

#ifndef LZZ_smtc_NonTypeParam_h
#define LZZ_smtc_NonTypeParam_h
// semantic
#include "smtc_CvType.h"
#include "smtc_Param.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NonTypeParam : public Param
  {
    int m_flags;
    CvType m_cv_type;
    gram::Block m_def_arg;
  public:
    NonTypeParam (int flags, CvType const & cv_type, NamePtr const & name, gram::Block const & def_arg);
    ~ NonTypeParam ();
    int getDeclSpec () const;
    CvType const & getCvType () const;
    bool hasDefaultArg () const;
    gram::Block const & getDefaultArg () const;
    util::String toString (bool is_decl) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NonTypeParam.inl"
#endif
#endif
