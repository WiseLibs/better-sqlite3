// gram_Message.cpp
//

#include "gram_Message.h"
// message
#include "msg_Message.h"
#include "msg_Output.h"
#define LZZ_INLINE inline
namespace gram
{
  namespace msg
  {
    using namespace ::msg;
  }
}
namespace gram
{
  namespace msg
  {
    void recoverOptSyntaxError ()
  {
    static char const str [] = "Syntax error in -r option.";
    print (Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void recoverOptNotAToken (util::String const & name)
  {
    static char const str [] = "'%1' is not a token in -r option.";
    print (Message (ERROR_MSG, str) << name);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void recoverOptNotACmd (util::String const & name)
  {
    static char const str [] = "'%1' is not a recover command in -r option.";
    print (Message (ERROR_MSG, str) << name);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void fileOpenError (util::Loc const & loc, char const * filename)
  {
    static char const str [] = "Unable to open file '%1'.";
    Message m (ERROR_MSG, str);
    m << filename;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void fileAccessError (util::Loc const & loc, char const * filename)
  {
    static char const str [] = "Error accessing file '%1'.";
    Message m (ERROR_MSG, str);
    m << filename;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidUniversalChar (util::Loc const & loc)
  {
    static char const str [] = "Ill-formed universal character.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidChar (util::Loc const & loc)
  {
    static char const str [] = "Invalid character.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void emptyLiteralChar (util::Loc const & loc)
  {
    static char const str [] = "Literal character is empty.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void eofInCComment (util::Loc const & loc)
  {
    static char const str [] = "Unexpected end of file inside c-style comment."; 
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingExponentInFloatingLiteral (util::Loc const & loc)
  {
    static char const str [] = "Missing exponent after 'e' or 'E' in floating literal; inserting '0'.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHexDigitsInIntLiteral (util::Loc const & loc)
  {
    static char const str [] = "Missing hex digits after '0x' in integer literal; inserting '0'.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidIntLiteralSuffix (util::Loc const & loc, char const * suffix, util::Ident const & lexeme)
  {
    static char const str [] = "Discarding invalid suffix '%1' after integer literal '%2'.";
    Message m (ERROR_MSG, str);
    print (loc, m << suffix << lexeme);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidFloatingLiteralSuffix (util::Loc const & loc, char const * suffix, util::Ident const & lexeme)
  {
    static char const str [] = "Discarding invalid suffix '%1' after floating literal '%2'.";
    Message m (ERROR_MSG, str);
    print (loc, m << suffix << lexeme);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHexDigitsInCharLiteral (util::Loc const & loc)
  {
    static char const str [] = "Missing hex digits after '\\x' in character literal.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void newlineInLiteralChar (util::Loc const & loc)
  {
    static char const str [] = "Newline in character literal.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void newlineInLiteralString (util::Loc const & loc)
  {
    static char const str [] = "Newline in string literal.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void eofInCodeBlock (util::Loc const & loc)
  {
    static char const str [] = "Unexpected end of file inside code block.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidEscInLiteralChar (util::Loc const & loc)
  {
    static char const str [] = "Invalid escape sequence.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void octalHasDigitsBeyondRadix (util::Loc const & loc, util::Ident const & lexeme)
  {
    static char const str [] = "Octal literal '%1' has digits beyond radix.";
    Message m (ERROR_MSG, str);
    m << lexeme;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void dblHashFirstOrLastToken (util::Loc const & loc)
  {
    static char const str [] = "'##' is not between two tokens.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void hashNotPrecedingParam (util::Loc const & loc)
  {
    static char const str [] = "'#' does not precede a macro parameter.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void badMacroNumArg (util::Loc const & loc, util::Ident const & name, int num_provided, int num_required)
  {
    static char const str [] = "%2 argument(s) provided to function macro '%1', %3 required.";
    Message m (ERROR_MSG, str);
    m << name;
    m << num_provided;
    m << num_required;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void badVarMacroNumArg (util::Loc const & loc, util::Ident const & name, int num_provided, int num_required)
  {
    static char const str [] = "%2 argument(s) provided to variadic function macro '%1', at least %3 required.";
    Message m (ERROR_MSG, str);
    m << name;
    m << num_provided;
    m << num_required;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void cannotConcatTokens (util::Loc const & loc, util::Ident const & lexeme1, util::Ident const & lexeme2, util::Loc const & prev_loc)
  {
    {
      static char const str [] = "Tokens '%1' and '%2' do not form a valid token when concatenated.";
      Message m (WARNING_MSG, str);
      m << lexeme1;
      m << lexeme2;
      print (loc, m);
    }
    {
      static char const str [] = "Concatenation performed here.";
      Message m (WARNING_MSG, str);
      print (prev_loc, m);
    }
  }
  }
}
namespace gram
{
  namespace msg
  {
    void funcMacroArgEmpty (util::Loc const & loc)
  {
    static char const str [] = "Function macro argument is empty.";
    Message m (WARNING_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void definedInIfMacro (util::Loc const & sub_loc, util::Loc const & def_loc)
  {
    {
      static char const str [] = "'defined' generated during macro substitution of #if line.";
      Message m (WARNING_MSG, str);
      print (sub_loc, m);
    }
    {
      static char const str [] = "'defined' token is here.";
      Message m (WARNING_MSG, str);
      print (def_loc, m);
    }
  }
  }
}
namespace gram
{
  namespace msg
  {
    void eofInMacroArgList (util::Loc const & loc)
  {
    static char const str [] = "Unexpected end of file inside function macro argument list.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void hashIfDivideByZero (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "0 divisor in #%1 expression.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIfDefinedRightParen (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Missing ')' after 'defined (IDENT' in #%1 expression.";
    Message m (WARNING_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIfDefinedIdent (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Missing 'defined' identifier in #%1 expression.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void hashIfSyntaxErrorBeforeToken (util::Loc const & loc, util::Ident const & dir_name, util::Ident const & lexeme)
  {
    static char const str [] = "Syntax error before '%2' in #%1 expression.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    m << lexeme;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void hashIfSyntaxErrorAtEol (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Syntax error at end of line in #%1 expression.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void macroParamListSyntaxErrorBeforeToken (util::Loc const & loc, util::Ident const & lexeme)
  {
    static char const str [] = "Syntax error before '%1' in macro parameter list.";
    Message m (ERROR_MSG, str);
    m << lexeme;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void macroParamListSyntaxErrorAtEol (util::Loc const & loc)
  {
    static char const str [] = "Syntax error at end of line in macro parameter list.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void duplicateMacroParam (util::Loc const & loc, util::Ident const & name)
  {
    static char const str [] = "'%1' is already used as a macro parameter name.";
    print (loc, Message (ERROR_MSG, str) << name);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void explicitVaArgsMacroParam (util::Loc const & loc)
  {
    static char const str [] = "'__VA_ARGS__' cannot be an explicit function macro parameter name.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void vaArgsUsedWithNamedVarArg (util::Loc const & loc)
  {
    static char const str [] = "'__VA_ARGS__' used in replacement set of function macro with named variable parameter.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void vaArgsUsedInNonVarMacro (util::Loc const & loc)
  {
    static char const str [] = "'__VA_ARGS__' used in replacement set of non-variadic function macro.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void elifWithoutIf (util::Loc const & loc)
  {
    static char const str [] = "#elif directive without preceding #if.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void elseWithoutIf (util::Loc const & loc)
  {
    static char const str [] = "#else directive without preceding #if.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void endifWithoutIf (util::Loc const & loc)
  {
    static char const str [] = "#endif directive without preceding #if.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIncludeFilename (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Missing filename after #%1 directive.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIncludeFilenameAfterMacroSub (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "No filename remains following macro substitution after #%1 directive.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidIncludeFilenameAfterMacroSub (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Invalid filename remains following macro substitution after #%1 directive.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void extraTokensFollowingDir (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Extra tokens following #%1 directive.";
    Message m (WARNING_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIfTokens (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Missing expression after #%1 directive";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashIfTokensAfterMacroSub (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "No expression remains following macro substitution after #%1 directive";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingMacroIdent (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Missing identifier after #%1 directive";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidMacroIdent (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "Invalid macro name after #%1 directive";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashLineTokens (util::Loc const & loc)
  {
    static char const str [] = "Missing tokens after #line directive";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHashLineTokensAfterMacroSub (util::Loc const & loc)
  {
    static char const str [] = "No tokens remain following macro substitution after #line directive";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidHashLine (util::Loc const & loc)
  {
    static char const str [] = "Expecting line number and optionally filename following macro substitution after #line directive";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void eofInFileBlock (util::Loc const & loc)
  {
    static char const str [] = "Missing #end in file block.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingEndif (util::Loc const & loc)
  {
    static char const str [] = "Missing #endif.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidDir (util::Loc const & loc)
  {
    static char const str [] = "Directive is not an identifier.";
    Message m (ERROR_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void unknownDir (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "'%1' is not a legal directive.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void dirInInvalidContext (util::Loc const & loc, util::Ident const & dir_name)
  {
    static char const str [] = "'#%1' is not valid in this context.";
    Message m (ERROR_MSG, str);
    m << dir_name;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void macroRedefined (util::Loc const & loc, util::Ident const & dir_name, util::Loc const & prev_loc)
  {
    {
      static char const str [] = "Macro '%1' is redefined.";
      Message m (WARNING_MSG, str);
      m << dir_name;
      print (loc, m);
    }
    {
      static char const str [] = "'%1' was previously defined here.";
      Message m (WARNING_MSG, str);
      m << dir_name;
      print (prev_loc, m);
    }
  }
  }
}
namespace gram
{
  namespace msg
  {
    void hashIncludeFileNotFound (util::Loc const & loc, util::Ident const & dir_name, util::String const & name, bool is_sys)
  {
    static char const usr_str [] = "#%1 file \"%2\" not found.";
    static char const sys_str [] = "#%1 file <%2> not found.";
    if (is_sys)
    {
      print (loc, Message (ERROR_MSG, sys_str) << dir_name << name); 
    }
    else
    {
      print (loc, Message (ERROR_MSG, usr_str) << dir_name << name); 
    }
  }
  }
}
namespace gram
{
  namespace msg
  {
    void hashError (util::Loc const & loc, util::String const & error_str)
  {
    static char const str [] = "#error: %1";
    Message m (ERROR_MSG, str);
    m << error_str;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void hashWarning (util::Loc const & loc, util::String const & warning_str)
  {
    static char const str [] = "#warning: %1";
    Message m (WARNING_MSG, str);
    m << warning_str;
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void hashIncludeDisabled (util::Loc const & loc)
  {
    static char const str [] = "#include and #insert directives are disabled.";
    Message m (WARNING_MSG, str);
    print (loc, m);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidPragmaInlFlag (util::Loc const & loc, util::Ident const & file_dir, util::Ident const & flag)
  {
    static char const str [] = "'%1' is not a valid flag for '%2' #pragma.  Expecting 'on' or 'off' (or 'yes' or 'no').";
    print (loc, Message (ERROR_MSG, str) << flag << file_dir);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidPragma (util::Loc const & loc, util::Ident const & name)
  {
    static char const str [] = "'%1' is not a valid lzz #pragma.";
    print (loc, Message (ERROR_MSG, str) << name);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingPragmaName (util::Loc const & loc)
  {
    static char const str [] = "Missing name after lzz #pragma.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void invalidPragmaFlag (util::Loc const & loc)
  {
    static char const str [] = "Expecting 'on' or 'off' (or 'yes' or 'no').";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void enumDecl (util::Loc const & loc)
  {
    static char const str [] = "An enum must be defined at its declaration.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void typenameDecl (util::Loc const & loc)
  {
    static char const str [] = "'typename' can not be used to declare a type.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void friendEnumDecl (util::Loc const & loc)
  {
    static char const str [] = "An enum cannot be declared as a friend.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void friendTypenameDecl (util::Loc const & loc)
  {
    static char const str [] = "'typename' can not be used to declare a friend type.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingTry (util::Loc const & loc)
  {
    static char const str [] = "Missing 'try' before function definition.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void missingHandlerSeq (util::Loc const & loc)
  {
    static char const str [] = "Missing try block handler sequence after function definition.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void typedefFuncDefn (util::Loc const & loc)
  {
    static char const str [] = "'typedef' cannot be used with a function definition.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void duplicateSpecifier (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "Duplicate declaration specifier: '%1'.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void conflictingSpecifier (util::Loc const & loc, char const * spec1, char const * spec2)
  {
    static char const str [] = "Conflicting declaration specifiers: '%1' and '%2'.";
    print (loc, Message (ERROR_MSG, str) << spec1 << spec2);
  }
  }
}
namespace gram
{
  namespace msg
  {
    void qualBitfield (util::Loc const & loc)
  {
    static char const str [] = "A bitfield name cannot be qualified.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void bitfieldTdef (util::Loc const & loc)
  {
    static char const str [] = "A bitfield name cannot be a typedef.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void vdfTypedef (util::Loc const & loc)
  {
    static char const str [] = "'typedef' ignored in VDF definition.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace gram
{
  namespace msg
  {
    void vdfFriend (util::Loc const & loc)
  {
    static char const str [] = "'friend' ignored in VDF definition.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
#undef LZZ_INLINE
