// util_String.h
//

#ifndef LZZ_util_String_h
#define LZZ_util_String_h
// std lib
#include <string>
#define LZZ_INLINE inline
namespace util
{
  typedef std::string String;
}
namespace util
{
  typedef std::string::iterator StringIter;
}
namespace util
{
  typedef std::string::const_iterator StringConstIter;
}
#undef LZZ_INLINE
#endif
