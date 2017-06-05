// smtc_HasLazyBaseSpecArg.cpp
//

#include "smtc_HasLazyBaseSpecArg.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_HasLazyBaseSpecArg.inl"
#endif
// std lib
#include <cstring>

// semantic
#include "smtc_LazyBaseSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool hasLazyBaseSpecArg (BaseSpecPtr const & base_spec, util::String const & arg)
  {
    bool result = false;
    if (base_spec->isLazy ())
    {
      LazyBaseSpec const & lazy_base_spec = static_cast <LazyBaseSpec const &> (* base_spec);
      gram::BlockVector const & arg_set = lazy_base_spec.getArgSet ();
      for (gram::BlockVectorConstIter beg = arg_set.begin (), end = arg_set.end (); beg != end; ++ beg)
      {
        if (beg->toString () == arg.c_str ())
        {
          result = true;
          break;
        }
      }
    }
    return result;
  }
}
namespace smtc
{
  HasLazyBaseSpecArg::~ HasLazyBaseSpecArg ()
              {}
}
#undef LZZ_INLINE
