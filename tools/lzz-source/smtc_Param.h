// smtc_Param.h
//

#ifndef LZZ_smtc_Param_h
#define LZZ_smtc_Param_h
// navg
#include "smtc_NamePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Param
  {
    NamePtr m_name;
  public:
    Param (NamePtr const & name);
    virtual ~ Param ();
    NamePtr const & getName () const;
    virtual util::String toString (bool is_decl) const = 0;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Param.inl"
#endif
#endif
