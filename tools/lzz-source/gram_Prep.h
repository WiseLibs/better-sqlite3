// gram_Prep.h
//

#ifndef LZZ_gram_Prep_h
#define LZZ_gram_Prep_h
// std lib
#include <map>
#include <set>
#include <cstdlib>

// gram
#include "gram_FileStatPtrVector.h"
#include "gram_MacroFilter.h"
#include "gram_CharBlock.h"

// basil
#include "basl_TokenDeque.h"

// semantic
#include "smtc_Output.h"
#include "smtc_SectionKind.h"

// util
#include "util_Filename.h"
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  class Lexer;
}
namespace gram
{
  struct Prep
  {
    smtc::Output * output;
    bool insert_all;
    basl::TokenDeque out_set;
    FileStatPtrVector fs_stack;
    FileMacroFilter macro_filter;
    bool lexing_line;
    bool from_file;
    bool real_mode;
    std::set <char const *> pragma_once_set;
    typedef std::map <char const *, util::Ident> GuardMap;
    typedef GuardMap::iterator GuardMapIter;
    GuardMap guard_map;
    Prep (util::String const & name, smtc::Output * output, bool insert_all = false);
    Prep (util::String const & str, util::Loc const & loc);
    bool fromFile () const;
    Lexer & getLexer () const;
    basl::TokenDeque & getPendingTokens ();
    void setRealMode (bool mode);
    bool hasPendingToken (basl::Token & token);
    void ungetToken (basl::Token const & token);
    basl::Token getNextToken ();
  private:
    void prepDefine (util::Loc const & dir_loc);
    bool hasPragmaOnce (char const * realname);
    bool hasGuard (char const * realname);
    void openIncludeFile (util::Ident const & dir_name, util::Loc const & name_loc, bool insert, util::String const & name, bool is_system);
    void prepInclude (util::Loc const & dir_loc, util::Ident const & dir_name, bool insert);
    void prepIf (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepIfdef (util::Loc const & dir_loc, util::Ident const & dir_name, bool is_ifndef);
    void prepElif (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepElse (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepEndif (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepUndef (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepLine (util::Loc const & dir_loc);
    void prepError (util::Loc const & dir_loc);
    void prepPragma (util::Loc const & dir_loc);
    void prepWarning (util::Loc const & dir_loc);
    Block prepFileBlock (util::Loc const & dir_loc, util::Ident dir_name);
    void printFileBlock (Block const & block, smtc::FilePtr const & file, smtc::SectionKind skind);
    void prepHdrBlock (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepSrcBlock (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepInlBlock (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepTplBlock (util::Loc const & dir_loc, util::Ident const & dir_name);
    void prepTnlBlock (util::Loc const & dir_loc, util::Ident const & dir_name);
  };
}
#undef LZZ_INLINE
#endif
