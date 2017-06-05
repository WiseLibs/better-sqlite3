// smtc_CreateNsEntity.cpp
//

#include "smtc_CreateNsEntity.h"
// semantic
#include "smtc_NsEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createNsEntity (NsPtr const & ns)
  {
    return new NsEntity (ns);
  }
}
#undef LZZ_INLINE
