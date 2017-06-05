// smtc_MbrInit.h
//

#ifndef LZZ_smtc_MbrInit_h
#define LZZ_smtc_MbrInit_h
// semantic
#include "smtc_NamePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class MbrInit
  {
    NamePtr m_name;
    util::String m_arg_set;
  public:
    MbrInit (NamePtr const & name, util::String const & arg_set);
    ~ MbrInit ();
    NamePtr const & getName () const;
    util::String const & getArgSet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_MbrInit.inl"
#endif
#endif
