// smtc_ConvBaseName.h
//

#ifndef LZZ_smtc_ConvBaseName_h
#define LZZ_smtc_ConvBaseName_h
// semantic
#include "smtc_BaseName.h"
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ConvBaseName : public BaseName
  {
    CvType m_cv_type;
  public:
    ConvBaseName (util::Loc const & loc, util::Ident const & macro, CvType const & cv_type);
    ~ ConvBaseName ();
    void accept (BaseNameVisitor const & visitor) const;
    CvType const & getCvType () const;
  };
}
#undef LZZ_INLINE
#endif
