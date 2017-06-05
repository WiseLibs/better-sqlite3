// smtc_HasLazyBaseSpecArg.h
//

#ifndef LZZ_smtc_HasLazyBaseSpecArg_h
#define LZZ_smtc_HasLazyBaseSpecArg_h
// semantic
#include "smtc_BaseSpecPtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool hasLazyBaseSpecArg (BaseSpecPtr const & base_spec, util::String const & arg);
}
namespace smtc
{
  struct HasLazyBaseSpecArg
  {
    util::String const & arg;
    bool operator () (BaseSpecPtr const & base_spec) const;
  public:
    explicit HasLazyBaseSpecArg (util::String const & arg);
    ~ HasLazyBaseSpecArg ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_HasLazyBaseSpecArg.inl"
#endif
#endif
