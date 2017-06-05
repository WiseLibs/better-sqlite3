// util_CharKeyTable.cpp
//

#include "util_CharKeyTable.h"
// util
#include "util_KeyTable.tpl"
#define LZZ_INLINE inline
namespace util
{
  template class Key <char>;
}
namespace util
{
  template class KeyTable <char>;
}
#undef LZZ_INLINE
