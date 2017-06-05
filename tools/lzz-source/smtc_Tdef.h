// smtc_Tdef.h
//

#ifndef LZZ_smtc_Tdef_h
#define LZZ_smtc_Tdef_h
// semantic
#include "smtc_CvType.h"
#include "smtc_Linkage.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Tdef
  {
    Linkage m_linkage;
    CvType m_cv_type;
    NamePtr m_name;
  public:
    Tdef (Linkage const & linkage, CvType const & cv_type, NamePtr const & name);
    ~ Tdef ();
    bool hasLinkage () const;
    Linkage const & getLinkage () const;
    CvType const & getCvType () const;
    NamePtr const & getName () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Tdef.inl"
#endif
#endif
