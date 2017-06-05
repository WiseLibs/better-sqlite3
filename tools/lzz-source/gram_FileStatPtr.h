// gram_FileStatPtr.h
//

#ifndef LZZ_gram_FileStatPtr_h
#define LZZ_gram_FileStatPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace gram
{
  class FileStat;
}
namespace gram
{
  typedef util::BPtr <FileStat> FileStatPtr;
}
#undef LZZ_INLINE
#endif
