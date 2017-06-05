// gram_Message.h
//

#ifndef LZZ_gram_Message_h
#define LZZ_gram_Message_h
// util
#include "util_Ident.h"
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  namespace msg
  {
    void recoverOptSyntaxError ();
  }
}
namespace gram
{
  namespace msg
  {
    void recoverOptNotAToken (util::String const & name);
  }
}
namespace gram
{
  namespace msg
  {
    void recoverOptNotACmd (util::String const & name);
  }
}
namespace gram
{
  namespace msg
  {
    void fileOpenError (util::Loc const & loc, char const * filename);
  }
}
namespace gram
{
  namespace msg
  {
    void fileAccessError (util::Loc const & loc, char const * filename);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidUniversalChar (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidChar (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void emptyLiteralChar (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void eofInCComment (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void missingExponentInFloatingLiteral (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHexDigitsInIntLiteral (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidIntLiteralSuffix (util::Loc const & loc, char const * suffix, util::Ident const & lexeme);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidFloatingLiteralSuffix (util::Loc const & loc, char const * suffix, util::Ident const & lexeme);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHexDigitsInCharLiteral (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void newlineInLiteralChar (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void newlineInLiteralString (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void eofInCodeBlock (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidEscInLiteralChar (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void octalHasDigitsBeyondRadix (util::Loc const & loc, util::Ident const & lexeme);
  }
}
namespace gram
{
  namespace msg
  {
    void dblHashFirstOrLastToken (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void hashNotPrecedingParam (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void badMacroNumArg (util::Loc const & loc, util::Ident const & name, int num_provided, int num_required);
  }
}
namespace gram
{
  namespace msg
  {
    void badVarMacroNumArg (util::Loc const & loc, util::Ident const & name, int num_provided, int num_required);
  }
}
namespace gram
{
  namespace msg
  {
    void cannotConcatTokens (util::Loc const & loc, util::Ident const & lexeme1, util::Ident const & lexeme2, util::Loc const & prev_loc);
  }
}
namespace gram
{
  namespace msg
  {
    void funcMacroArgEmpty (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void definedInIfMacro (util::Loc const & sub_loc, util::Loc const & def_loc);
  }
}
namespace gram
{
  namespace msg
  {
    void eofInMacroArgList (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void hashIfDivideByZero (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIfDefinedRightParen (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIfDefinedIdent (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void hashIfSyntaxErrorBeforeToken (util::Loc const & loc, util::Ident const & dir_name, util::Ident const & lexeme);
  }
}
namespace gram
{
  namespace msg
  {
    void hashIfSyntaxErrorAtEol (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void macroParamListSyntaxErrorBeforeToken (util::Loc const & loc, util::Ident const & lexeme);
  }
}
namespace gram
{
  namespace msg
  {
    void macroParamListSyntaxErrorAtEol (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void duplicateMacroParam (util::Loc const & loc, util::Ident const & name);
  }
}
namespace gram
{
  namespace msg
  {
    void explicitVaArgsMacroParam (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void vaArgsUsedWithNamedVarArg (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void vaArgsUsedInNonVarMacro (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void elifWithoutIf (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void elseWithoutIf (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void endifWithoutIf (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIncludeFilename (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIncludeFilenameAfterMacroSub (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidIncludeFilenameAfterMacroSub (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void extraTokensFollowingDir (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIfTokens (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIfTokensAfterMacroSub (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void missingMacroIdent (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidMacroIdent (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashLineTokens (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashLineTokensAfterMacroSub (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidHashLine (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void eofInFileBlock (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void missingEndif (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidDir (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void unknownDir (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void dirInInvalidContext (util::Loc const & loc, util::Ident const & dir_name);
  }
}
namespace gram
{
  namespace msg
  {
    void macroRedefined (util::Loc const & loc, util::Ident const & dir_name, util::Loc const & prev_loc);
  }
}
namespace gram
{
  namespace msg
  {
    void hashIncludeFileNotFound (util::Loc const & loc, util::Ident const & dir_name, util::String const & name, bool is_sys = false);
  }
}
namespace gram
{
  namespace msg
  {
    void hashError (util::Loc const & loc, util::String const & error_str);
  }
}
namespace gram
{
  namespace msg
  {
    void hashWarning (util::Loc const & loc, util::String const & warning_str);
  }
}
namespace gram
{
  namespace msg
  {
    void hashIncludeDisabled (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidPragmaInlFlag (util::Loc const & loc, util::Ident const & file_dir, util::Ident const & flag);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidPragma (util::Loc const & loc, util::Ident const & name);
  }
}
namespace gram
{
  namespace msg
  {
    void missingPragmaName (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void invalidPragmaFlag (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void enumDecl (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void typenameDecl (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void friendEnumDecl (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void friendTypenameDecl (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void missingTry (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void missingHandlerSeq (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void typedefFuncDefn (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void duplicateSpecifier (util::Loc const & loc, char const * spec);
  }
}
namespace gram
{
  namespace msg
  {
    void conflictingSpecifier (util::Loc const & loc, char const * spec1, char const * spec2);
  }
}
namespace gram
{
  namespace msg
  {
    void qualBitfield (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void bitfieldTdef (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void vdfTypedef (util::Loc const & loc);
  }
}
namespace gram
{
  namespace msg
  {
    void vdfFriend (util::Loc const & loc);
  }
}
#undef LZZ_INLINE
#endif
