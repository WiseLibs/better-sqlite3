// smtc_UnqlName.h
//

#ifndef LZZ_smtc_UnqlName_h
#define LZZ_smtc_UnqlName_h
#include "smtc_BaseNamePtr.h"
#include "smtc_Name.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UnqlName : public Name
  {
    BaseNamePtr m_base_name;
  public:
    UnqlName (BaseNamePtr const & base_name);
    ~ UnqlName ();
    util::Loc const & getLoc () const;
    BaseNamePtr const & getBaseName () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_UnqlName.inl"
#endif
#endif
