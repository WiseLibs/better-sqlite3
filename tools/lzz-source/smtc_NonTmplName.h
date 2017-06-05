// smtc_NonTmplName.h
//

#ifndef LZZ_smtc_NonTmplName_h
#define LZZ_smtc_NonTmplName_h
#include "smtc_UnqlName.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NonTmplName : public UnqlName
  {
  public:
    NonTmplName (BaseNamePtr const & base_name);
    ~ NonTmplName ();
    void accept (NameVisitor const & visitor) const;
  };
}
#undef LZZ_INLINE
#endif
