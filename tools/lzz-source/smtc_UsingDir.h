// smtc_UsingDir.h
//

#ifndef LZZ_smtc_UsingDir_h
#define LZZ_smtc_UsingDir_h
// semantic
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UsingDir
  {
    NamePtr m_name;
  public:
    UsingDir (NamePtr const & name);
    ~ UsingDir ();
    NamePtr const & getName () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_UsingDir.inl"
#endif
#endif
