// smtc_ConvBaseName.cpp
//

#include "smtc_ConvBaseName.h"
// semantic
#include "smtc_BaseNameVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  ConvBaseName::ConvBaseName (util::Loc const & loc, util::Ident const & macro, CvType const & cv_type)
    : BaseName (loc, macro), m_cv_type (cv_type)
    {}
}
namespace smtc
{
  ConvBaseName::~ ConvBaseName ()
    {}
}
namespace smtc
{
  void ConvBaseName::accept (BaseNameVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  CvType const & ConvBaseName::getCvType () const
    {
      return m_cv_type;
    }
}
#undef LZZ_INLINE
