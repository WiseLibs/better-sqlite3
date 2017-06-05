// smtc_BuildLazyClassMbrInitSet.cpp
//

#include "smtc_BuildLazyClassMbrInitSet.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_CreateMbrInit.h"
#include "smtc_LazyBaseSpec.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct BuildMbrInitIfLazy
  {
    MbrInitPtrVector & mbr_init_set;
    void operator () (BaseSpecPtr const & base_spec) const;
  public:
    explicit BuildMbrInitIfLazy (MbrInitPtrVector & mbr_init_set);
    ~ BuildMbrInitIfLazy ();
  };
}
namespace
{
  void BuildMbrInitIfLazy::operator () (BaseSpecPtr const & base_spec) const
  {
    if (base_spec->isLazy ())
    {
      LazyBaseSpec const & lazy_base_spec = static_cast <LazyBaseSpec const &> (* base_spec);
      MbrInitPtr mbr_init = createMbrInit (lazy_base_spec.getBaseName (), lazy_base_spec.getArgSet ());
      mbr_init_set.push_back (mbr_init);
    }
  }
}
namespace
{
  LZZ_INLINE BuildMbrInitIfLazy::BuildMbrInitIfLazy (MbrInitPtrVector & mbr_init_set)
    : mbr_init_set (mbr_init_set)
       {}
}
namespace
{
  BuildMbrInitIfLazy::~ BuildMbrInitIfLazy ()
       {}
}
namespace smtc
{
  void buildLazyClassMbrInitSet (BaseSpecPtrVector const & base_spec_set, MbrInitPtrVector & mbr_init_set)
  {
    std::for_each (base_spec_set.begin (), base_spec_set.end (), BuildMbrInitIfLazy (mbr_init_set));
  }
}
#undef LZZ_INLINE
