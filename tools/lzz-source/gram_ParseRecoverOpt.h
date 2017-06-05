// gram_ParseRecoverOpt.h
//

#ifndef LZZ_gram_ParseRecoverOpt_h
#define LZZ_gram_ParseRecoverOpt_h
// std lib
#include <iosfwd>

// basil
#include "basl_ErrorRec.h"
#define LZZ_INLINE inline
namespace gram
{
  void parseRecoverOpt (basl::ErrorRec & error_rec);
}
namespace gram
{
  void printRecoverTokens (std::ostream & os);
}
namespace gram
{
  void printRecoverHelp (std::ostream & os);
}
#undef LZZ_INLINE
#endif
