// smtc_GlobalNs.h
//

#ifndef LZZ_smtc_GlobalNs_h
#define LZZ_smtc_GlobalNs_h
// semantic
#include "smtc_Ns.h"
#define LZZ_INLINE inline
namespace smtc
{
  class GlobalNs : public Ns
  {
  public:
    GlobalNs ();
    ~ GlobalNs ();
    void accept (NsVisitor const & visitor) const;
  };
}
#undef LZZ_INLINE
#endif
