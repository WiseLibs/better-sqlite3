// gram_MacroFilter.h
//

#ifndef LZZ_gram_MacroFilter_h
#define LZZ_gram_MacroFilter_h
// gram
#include "gram_MacroArgPtrVector.h"
#include "gram_MacroPtr.h"

// basil
#include "basl_TokenDeque.h"
#include "basl_TokenVector.h"

// util
#include "util_IdentVector.h"
#define LZZ_INLINE inline
namespace gram
{
  class MacroFilter
  {
    bool is_final;
    bool is_if;
    util::IdentVector & history;
    basl::TokenDeque & out_set;
    enum State
    {
      START_STATE,
      IF_DEFINED_STATE,
      IF_DEFINED_LPAREN_STATE,
      MAYBE_FUNC_STATE,
      FUNC_ARG_STATE
    };
    State state;
    MacroPtr func_macro;
    basl::Token func_macro_token;
    bool var;
    int num_param;
    int nest;
    basl::TokenVector arg_token_set;
    MacroArgPtrVector arg_set;
    bool is_sub;
    util::Loc sub_loc;
  public:
    void next (basl::TokenVector const & in_set);
    void next (basl::Token const & in_token);
    void flush ();
  private:
    bool isMacroInHistory (util::Ident const & name);
    basl::Token getPassToken (basl::Token const & token);
    void passToken (basl::Token const & token);
    void subObjRepSet (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set);
    void subObjRepSet (util::Ident const & name, basl::TokenVector const & rep_set);
    void subFuncRepSet (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set, MacroArgPtrVector const & arg_set, bool var);
    void subFuncRepSet (util::Ident const & name, basl::TokenVector const & rep_set, MacroArgPtrVector const & arg_set, bool var);
    void next (util::Ident const & name, basl::TokenVector const & in_set);
  public:
    explicit MacroFilter (bool is_final, bool is_if, util::IdentVector & history, basl::TokenDeque & out_set);
    ~ MacroFilter ();
  };
}
namespace gram
{
  class FileMacroFilter : public MacroFilter
  {
    util::IdentVector history;
  public:
    explicit FileMacroFilter (basl::TokenDeque & out_set);
    ~ FileMacroFilter ();
  };
}
namespace gram
{
  class HashIfMacroFilter : public MacroFilter
  {
    util::IdentVector history;
  public:
    explicit HashIfMacroFilter (basl::TokenDeque & out_set);
    ~ HashIfMacroFilter ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_MacroFilter.inl"
#endif
#endif
