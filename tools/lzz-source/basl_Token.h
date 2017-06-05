// basl_Token.h
//

#ifndef LZZ_basl_Token_h
#define LZZ_basl_Token_h
// basil
#include "basl_TokenFlags.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace basl
{
  class Token
  {
    int m_flags;
    int m_number;
    util::Loc m_loc;
    util::Ident m_lexeme;
  public:
    Token ();
    Token (int number, util::Loc const & loc, util::Ident const & lexeme);
    ~ Token ();
    bool isSet () const;
    void setSpaceBefore ();
    bool hasSpaceBefore () const;
    void setRecSubMacro ();
    bool isRecSubMacro () const;
    bool fromMacro () const;
    void setFromMacro ();
    int getNumber () const;
    void setNumber (int number);
    util::Ident const & getLexeme () const;
    void setLexeme (util::Ident const & lexeme);
    util::Loc const & getLoc () const;
    void setLoc (util::Loc const & loc);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_Token.inl"
#endif
#endif
