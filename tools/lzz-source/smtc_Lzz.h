// smtc_Lzz.h
//

#ifndef LZZ_smtc_Lzz_h
#define LZZ_smtc_Lzz_h
// std lib
#include <iosfwd>

// util
#include "util_StringDeque.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Output;
}
namespace smtc
{
  bool isHelpOptionSet ();
}
namespace smtc
{
  bool isPreprocessOptionSet ();
}
namespace smtc
{
  void printLzzHelp (std::ostream & os);
}
namespace smtc
{
  void preprocessFile (util::String const & filename, std::ostream & os);
}
namespace smtc
{
  void translateFile (util::String const & filename, Output & output);
}
namespace smtc
{
  void compileFiles (util::StringDeque const & filenames, std::ostream & os);
}
#undef LZZ_INLINE
#endif
