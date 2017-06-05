// util_Rewind.cpp
//

#include "util_Rewind.h"
#include <iostream>
#define LZZ_INLINE inline
namespace util
{
  void rewind (std::istream & is)
  {
    is.seekg (0, std::ios_base::beg);
  }
}
#undef LZZ_INLINE
