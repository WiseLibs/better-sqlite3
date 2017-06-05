// smtc_GetElabType.cpp
//

#include "smtc_GetElabType.h"
// semantic
#include "smtc_ElabType.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getElabType (ClassKey key, NamePtr const & name)
  {
    return new ElabType (key, name);
  }
}
#undef LZZ_INLINE
