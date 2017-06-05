// util_Rewind.h
//

#ifndef LZZ_util_Rewind_h
#define LZZ_util_Rewind_h
#include <iosfwd>
#define LZZ_INLINE inline
namespace util
{
  void rewind (std::istream & is);
}
#undef LZZ_INLINE
#endif
