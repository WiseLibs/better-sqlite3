// smtc_EntityPtr.h
//

#ifndef LZZ_smtc_EntityPtr_h
#define LZZ_smtc_EntityPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Entity;
}
namespace smtc
{
  typedef util::BPtr <Entity> EntityPtr;
}
#undef LZZ_INLINE
#endif
