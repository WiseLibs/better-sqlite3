// gram_PrettyPrintTokens.h
//

#ifndef LZZ_gram_PrettyPrintTokens_h
#define LZZ_gram_PrettyPrintTokens_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_SectionKind.h"

// basil
#include "basl_TokenDeque.h"

#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  class Filename;
}
namespace gram
{
  void prettyPrintTokens (smtc::FilePtr const & file, smtc::SectionKind skind, util::Loc const & start_loc, basl::TokenDeque const & tokens);
}
namespace gram
{
  util::String prettyPrintTokensToString (basl::TokenDeque const & tokens);
}
namespace gram
{
  void prettyPrintTokensToStream (std::ostream & os, basl::TokenDeque const & tokens);
}
#undef LZZ_INLINE
#endif
