// smtc_LazyBaseSpec.h
//

#ifndef LZZ_smtc_LazyBaseSpec_h
#define LZZ_smtc_LazyBaseSpec_h
// semantic
#include "smtc_BaseSpec.h"

// gram
#include "gram_BlockVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class LazyBaseSpec : public BaseSpec
  {
    gram::BlockVector m_arg_set;
  public:
    LazyBaseSpec (Access access, bool is_virtual, NamePtr const & base_name, gram::BlockVector const & arg_set);
    ~ LazyBaseSpec ();
    gram::BlockVector const & getArgSet () const;
    bool isLazy () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_LazyBaseSpec.inl"
#endif
#endif
