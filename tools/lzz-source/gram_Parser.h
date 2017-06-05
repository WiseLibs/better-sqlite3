// gram_Parser.h
//

#ifndef LZZ_gram_Parser_h
#define LZZ_gram_Parser_h
// semantic
#include "smtc_Output.h"
#include "smtc_ScopePtr.h"

// basil
#include "basl_SyntaxTree.h"
#include "basl_TokenDeque.h"

// util
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  void parse (util::String const & filename, smtc::ScopePtr const & scope, smtc::Output & output);
}
namespace gram
{
  basl::SyntaxTree parseString (util::String const & str, util::Loc const & loc, int state, smtc::ScopePtr const & scope);
}
namespace gram
{
  void ppParse (util::String const & filename, basl::TokenDeque & token_set);
}
#undef LZZ_INLINE
#endif
