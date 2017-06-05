// util_IntKeyTable.cpp
//

#include "util_IntKeyTable.h"
// util
#include "util_KeyTable.tpl"
#define LZZ_INLINE inline
namespace util
{
  template class Key <size_t>;
}
namespace util
{
  template class KeyTable <size_t>;
}
#undef LZZ_INLINE
