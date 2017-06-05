// conf_PrintHelp.h
//

#ifndef LZZ_conf_PrintHelp_h
#define LZZ_conf_PrintHelp_h
// std lib
#include <iostream>
#define LZZ_INLINE inline
namespace conf
{
  void printVersion (std::ostream & os);
}
namespace conf
{
  void printHelp (std::ostream & os);
}
#undef LZZ_INLINE
#endif
