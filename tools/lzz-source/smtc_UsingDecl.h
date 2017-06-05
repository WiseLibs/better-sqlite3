// smtc_UsingDecl.h
//

#ifndef LZZ_smtc_UsingDecl_h
#define LZZ_smtc_UsingDecl_h
// semantic
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UsingDecl
  {
    NamePtr m_name;
  public:
    UsingDecl (NamePtr const & name);
    ~ UsingDecl ();
    NamePtr const & getName () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_UsingDecl.inl"
#endif
#endif
