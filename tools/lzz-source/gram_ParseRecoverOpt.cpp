// gram_ParseRecoverOpt.cpp
//

#include "gram_ParseRecoverOpt.h"
// std lib
#include <algorithm>
#include <cstdlib>
#include <iostream>

// gram
#include "gram_Message.h"
#include "gram_TokenNumber.h"

// util
#include "util_Exception.h"
#include "util_GetIdent.h"
#include "util_GetNextWord.h"
#include "util_RemoveChars.h"
#include "util_StringICompare.h"

// config
#include "conf_Config.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  using namespace util;
}
namespace
{
  struct TokenRec
  {
    char const * name;
    int number;
    char const * lexeme;
  };
}
namespace
{
  TokenRec (token_rec_set) [] =
  {
    { "AND", AND_TOKEN, "&&" },
    { "ASSIGN", ASSIGN_TOKEN, "=" },
    { "AUTO", AUTO_TOKEN, "auto" },
    { "BITAND", BITAND_TOKEN, "&" },
    { "BITAND_ASSIGN", BITAND_ASSIGN_TOKEN, "&=" },
    { "BITNOT", BITNOT_TOKEN, "~" },
    { "BITOR", BITOR_TOKEN, "|" },
    { "BITOR_ASSIGN", BITOR_ASSIGN_TOKEN, "|=" },
    { "BOOL", BOOL_TOKEN, "bool" },
    { "CATCH", CATCH_TOKEN, "catch" },
    { "CHAR", CHAR_TOKEN, "char" },
    { "CLASS", CLASS_TOKEN, "class" },
    { "COLON", COLON_TOKEN, ":" },
    { "COMMA", COMMA_TOKEN, "," },
    { "CONST", CONST_TOKEN, "const" },
    { "DCOLON", DCOLON_TOKEN, "::" },
    { "DEC", DEC_TOKEN, "--" },
    { "DELETE", DELETE_TOKEN, "delete" },
    { "DINIT", DINIT_TOKEN, "_dinit" },
    { "DIVIDE", DIVIDE_TOKEN, "/" },
    { "DIVIDE_ASSIGN", DIVIDE_ASSIGN_TOKEN, "/=" },
    { "DOUBLE", DOUBLE_TOKEN, "double" },
    { "ELLIPSE", ELLIPSE_TOKEN, "..." },
    { "ENUM", ENUM_TOKEN, "enum" },
    { "EQ", EQ_TOKEN, "==" },
    { "EXPLICIT", EXPLICIT_TOKEN, "explicit" },
    { "EXTERN", EXTERN_TOKEN, "extern" },
    { "FLOAT", FLOAT_TOKEN, "float" },
    { "FRIEND", FRIEND_TOKEN, "friend" },
    { "GT", GT_TOKEN, ">" },
    { "GTEQ", GTEQ_TOKEN, ">=" },
    { "IDENT", IDENT_TOKEN, "<identifier>" },
    { "INC", INC_TOKEN, "++" },
    { "INLINE", INLINE_TOKEN, "inline" },
    { "INT", INT_TOKEN, "int" },
    { "LBRACE", LBRACE_TOKEN, "{" },
    { "LBRACK", LBRACK_TOKEN, "[" },
    { "LONG", LONG_TOKEN, "long" },
    { "LPAREN", LPAREN_TOKEN, "(" },
    { "LSHIFT", LSHIFT_TOKEN, "<<" },
    { "LSHIFT_ASSIGN", LSHIFT_ASSIGN_TOKEN, "<<=" },
    { "LT", LT_TOKEN, "<" },
    { "LTEQ", LTEQ_TOKEN, "<=" },
    { "MINUS", MINUS_TOKEN, "-" },
    { "MINUS_ASSIGN", MINUS_ASSIGN_TOKEN, "-=" },
    { "MOD", MOD_TOKEN, "%" },
    { "MOD_ASSIGN", MOD_ASSIGN_TOKEN, "%=" },
    { "MUTABLE", MUTABLE_TOKEN, "mutable" },
    { "NAMESPACE", NAMESPACE_TOKEN, "namespace" },
    { "NEW", NEW_TOKEN, "new" },
    { "NOT", NOT_TOKEN, "!" },
    { "NOTEQ", NOTEQ_TOKEN, "!=" },
    { "OPERATOR", OPERATOR_TOKEN, "operator" },
    { "OR", OR_TOKEN, "||" },
    { "PLUS", PLUS_TOKEN, "+" },
    { "PLUS_ASSIGN", PLUS_ASSIGN_TOKEN, "+=" },
    { "PRIVATE", PRIVATE_TOKEN, "private" },
    { "PROTECTED", PROTECTED_TOKEN, "protected" },
    { "PTR", PTR_TOKEN, "->" },
    { "PTR_TIMES", PTR_TIMES_TOKEN, "->*" },
    { "PUBLIC", PUBLIC_TOKEN, "public" },
    { "RBRACE", RBRACE_TOKEN, "}" },
    { "RBRACK", RBRACK_TOKEN, "]" },
    { "REGISTER", REGISTER_TOKEN, "register" },
    { "RPAREN", RPAREN_TOKEN, ")" },
    { "RSHIFT", RSHIFT_TOKEN, ">>" },
    { "RSHIFT_ASSIGN", RSHIFT_ASSIGN_TOKEN, ">>=" },
    { "SEMI", SEMI_TOKEN, ";" },
    { "SHORT", SHORT_TOKEN, "short" },
    { "SIGNED", SIGNED_TOKEN, "signed" },
    { "STATIC", STATIC_TOKEN, "static" },
    { "STRUCT", STRUCT_TOKEN, "struct" },
    { "TEMPLATE", TEMPLATE_TOKEN, "template" },
    { "THROW", THROW_TOKEN, "throw" },
    { "TIMES", TIMES_TOKEN, "*" },
    { "TIMES_ASSIGN", TIMES_ASSIGN_TOKEN, "*=" },
    { "TRY", TRY_TOKEN, "try" },
    { "TYPEDEF", TYPEDEF_TOKEN, "typedef" },
    { "TYPENAME", TYPENAME_TOKEN, "typename" },
    { "UNION", UNION_TOKEN, "union" },
    { "UNSIGNED", UNSIGNED_TOKEN, "unsigned" },
    { "USING", USING_TOKEN, "using" },
    { "VIRTUAL", VIRTUAL_TOKEN, "virtual" },
    { "VOID", VOID_TOKEN, "void" },
    { "VOLATILE", VOLATILE_TOKEN, "volatile" },
    { "WCHAR", WCHAR_TOKEN, "wchar_t" },
    { "XOR", XOR_TOKEN, "^" },
    { "XOR_ASSIGN", XOR_ASSIGN_TOKEN, "^=" },
    { "ZERO", ZERO_TOKEN, "0" },
  };
}
namespace
{
  struct CmpTokenRecName
  {
    bool operator () (TokenRec const & rec, char const * name) const;
  public:
    explicit CmpTokenRecName ();
    ~ CmpTokenRecName ();
  };
}
namespace
{
  struct PrintTokenRecNameAndLexeme
  {
    std::ostream & os;
    void operator () (TokenRec const & rec) const;
  public:
    explicit PrintTokenRecNameAndLexeme (std::ostream & os);
    ~ PrintTokenRecNameAndLexeme ();
  };
}
namespace
{
  bool lookupToken (char const * name, int & number, Ident & lexeme);
}
namespace
{
  struct ParseRecoverOpt
  {
    StringConstIter str_beg;
    StringConstIter str_end;
    basl::ErrorRec & error_rec;
    static void syntaxError ();
    static void notAToken (util::String const & name);
    static void notACmd (util::String const & name);
    void parseNumber (int & number);
    void parseToken (int & number, Ident & lexeme);
    void parseFreeTokenSet (basl::FreeTokenVector & free_token_set);
    void parseICmd ();
    void parseRCmd ();
    void parseDCmd ();
    void parseMCmd ();
    void parse ();
  public:
    explicit ParseRecoverOpt (StringConstIter str_beg, StringConstIter str_end, basl::ErrorRec & error_rec);
    ~ ParseRecoverOpt ();
  };
}
namespace
{
  char const (help_text) [] =
  {
    "One or more recover commands can be specifed using the -r option.\n"
    "The commands must be comma delimited. The valid commands are:\n"
    " i:TOKEN\n"
    "   insert TOKEN\n"
    " i:[TOKEN,TOKEN,...]\n"
    "   insert a sequence of TOKENs \n"
    " d\n"
    "   delete one token\n"
    " d:MAX_NUM\n"
    "   delete at most MAX_NUM tokens\n"
    " d:TOKEN\n"
    "   delete TOKEN\n"
    " r:TOKEN\n"
    "   replace one token with TOKEN\n"
    " r:TOKEN:MAX_NUM\n"
    "   replace at most MAX_NUM tokens with TOKEN\n"
    " r:TOKEN:TOKEN\n"
    "   replace (second) TOKEN with (first) TOKEN\n"
    " r:[TOKEN,TOKEN,...]\n"
    "   replace one token with a sequence of TOKENs\n"
    " r:[TOKEN,TOKEN,...]:MAX_NUM\n"
    "   replace at most MAX_NUM tokens with a sequence of TOKENs\n"
    " r:[TOKEN,TOKEN,...]:TOKEN\n"
    "   replace TOKEN with a sequence of tokens\n"
    " m\n"
    "   move one token after one token to the right\n"
    " m:MAX_MOVE\n"
    "   move one token after at most MAX_MOVE tokens to the right\n"
    " m:MAX_MOVE:MAX_NUM\n"
    "   move at most MAX_NUM tokens after at most MAX_MOVE tokens to the right\n"
    "TOKEN is a token name. Type 'lzz -T' to print the list of valid\n"
    "token names. The recover commands can also be set in the environment\n"
    "variable LZZ_SYNTAX_RECOVER_COMMANDS. An example recover command\n"
    "sequence is: i:IDENT,i:SEMI,i:INT,m,d:30\n"
  };
}
namespace
{
  LZZ_INLINE bool CmpTokenRecName::operator () (TokenRec const & rec, char const * name) const
  {
    return stringICompare (rec.name, name) == -1;
  }
}
namespace
{
  LZZ_INLINE CmpTokenRecName::CmpTokenRecName ()
              {}
}
namespace
{
  CmpTokenRecName::~ CmpTokenRecName ()
              {}
}
namespace
{
  void PrintTokenRecNameAndLexeme::operator () (TokenRec const & rec) const
  {
    os << ' ' << rec.name << ' ' << rec.lexeme << '\n';
  }
}
namespace
{
  LZZ_INLINE PrintTokenRecNameAndLexeme::PrintTokenRecNameAndLexeme (std::ostream & os)
    : os (os)
       {}
}
namespace
{
  PrintTokenRecNameAndLexeme::~ PrintTokenRecNameAndLexeme ()
       {}
}
namespace
{
  bool lookupToken (char const * name, int & number, Ident & lexeme)
  {
    bool result = false;
    TokenRec const * beg = token_rec_set;
    TokenRec const * end = token_rec_set + sizeof (token_rec_set) / sizeof (token_rec_set [0]);
    TokenRec const * i = std::lower_bound (beg, end, name, CmpTokenRecName ());
    if (i != end && stringICompare (i->name, name) == 0)
    {
      number = i->number;
      lexeme = getIdent (i->lexeme);
      result = true;
    }
    return result;
  }
}
namespace
{
  void ParseRecoverOpt::syntaxError ()
    {
      msg::recoverOptSyntaxError ();
      throw Exception ();
    }
}
namespace
{
  void ParseRecoverOpt::notAToken (util::String const & name)
    {
      msg::recoverOptNotAToken (name);
      throw Exception ();
    }
}
namespace
{
  void ParseRecoverOpt::notACmd (util::String const & name)
    {
      msg::recoverOptNotACmd (name);
      throw Exception ();
    }
}
namespace
{
  void ParseRecoverOpt::parseNumber (int & number)
    {
      String word = getNextWord (str_beg, str_end, ",]:", str_beg);
      number = atoi (word.c_str ());
    }
}
namespace
{
  void ParseRecoverOpt::parseToken (int & number, Ident & lexeme)
    {
      String word = getNextWord (str_beg, str_end, ",]:", str_beg);
      if (word.empty ())
      {
        syntaxError ();
      }
      if (! lookupToken (word.c_str (), number, lexeme))
      {
        notAToken (word);
      }
    }
}
namespace
{
  void ParseRecoverOpt::parseFreeTokenSet (basl::FreeTokenVector & free_token_set)
    {
      if (* str_beg != '[' || ++ str_beg == str_end)
      {
        syntaxError ();
      }
      for (;;)
      {
        int number;
        Ident lexeme;
        parseToken (number, lexeme);
        free_token_set.push_back (basl::FreeToken (number, lexeme));
        if (str_beg != str_end && * str_beg == ']')
        {
          ++ str_beg;
          break;
        }
        if (str_beg == str_end || * str_beg != ',' || ++ str_beg == str_end)
        {
          syntaxError ();
        }
      }
    }
}
namespace
{
  void ParseRecoverOpt::parseICmd ()
    {
      if (str_beg == str_end || * str_beg != ':' || ++ str_beg == str_end)
      {
        syntaxError ();
      }
      basl::FreeTokenVector free_token_set;
      if (* str_beg == '[')
      {
        parseFreeTokenSet (free_token_set);
      }
      else
      {
        int number;
        Ident lexeme;
        parseToken (number, lexeme);
        free_token_set.push_back (basl::FreeToken (number, lexeme));
      }
      error_rec.insertSome (free_token_set);
    }
}
namespace
{
  void ParseRecoverOpt::parseRCmd ()
    {
      if (str_beg == str_end || * str_beg != ':' || ++ str_beg == str_end)
      {
        syntaxError ();
      }
      basl::FreeTokenVector free_token_set;
      if (* str_beg == '[')
      {
        parseFreeTokenSet (free_token_set);
      }
      else
      {
        int number;
        Ident lexeme;
        parseToken (number, lexeme);
        free_token_set.push_back (basl::FreeToken (number, lexeme));
      }
      if (str_beg == str_end || * str_beg != ':')
      {
        // r:[TOKEN,TOKEN,...]
        // r:TOKEN
        error_rec.replaceSome (1, free_token_set);
      }
      else
      {
        if (++ str_beg == str_end)
        {
          syntaxError ();
        }
        if (isdigit (* str_beg))
        {
          // r:[TOKEN,TOKEN,...]:NUMBER
          // r:TOKEN:NUMBER
          int max_discard;
          parseNumber (max_discard);
          error_rec.replaceSome (max_discard, free_token_set);
        }
        else
        {
          // r:[TOKEN,TOKEN,...]:TOKEN
          // r:TOKEN:TOKEN
          int number;
          Ident lexeme;
          parseToken (number, lexeme);
          error_rec.replaceOne (number, free_token_set);
        }
      }
    }
}
namespace
{
  void ParseRecoverOpt::parseDCmd ()
    {
      if (str_beg == str_end || * str_beg != ':')
      {
        // d
        error_rec.discardSome (1);
      }
      else
      {
        if (++ str_beg == str_end)
        {
          syntaxError ();
        }
        if (isdigit (* str_beg))
        {
          // d:NUMBER
          int max_discard;
          parseNumber (max_discard);
          error_rec.discardSome (max_discard);
        }
        else
        {
          // d:TOKEN
          int number;
          Ident lexeme;
          parseToken (number, lexeme);
          error_rec.discardOne (number);
        }
      }
    }
}
namespace
{
  void ParseRecoverOpt::parseMCmd ()
    {
      basl::RecCmdPtr rec_cmd;
      if (str_beg == str_end || * str_beg != ':')
      {
        // m
        error_rec.moveSome (1, 1);
      }
      else
      {
        if (++ str_beg == str_end || ! isdigit (* str_beg))
        {
          syntaxError ();
        }
        int max_move = 1;
        parseNumber (max_move);
        if (str_beg == str_end || * str_beg != ':')
        {
          // m:NUMBER
          error_rec.moveSome (max_move, 1);
        }
        else
        {
          if (++ str_beg == str_end || ! isdigit (* str_beg))
          {
            syntaxError ();
          }
          int max_num = 1;
          parseNumber (max_num);
          // m:NUMBER:NUMBER
          error_rec.moveSome (max_move, max_num);
        }
      }
    }
}
namespace
{
  void ParseRecoverOpt::parse ()
    {
      for (;;)
      {
        String word = getNextWord (str_beg, str_end, ":,", str_beg);
        if (word == "i")
        {
          parseICmd ();
        }
        else if (word == "d")
        {
          parseDCmd ();
        }
        else if (word == "r")
        {
          parseRCmd ();
        }
        else if (word == "m")
        {
          parseMCmd ();
        }
        else
        {
          notACmd (word);
        }
        if (str_beg == str_end)
        {
          break;
        }
        if (* str_beg != ',' || ++ str_beg == str_end)
        {
          syntaxError ();
        }
      }
    }
}
namespace
{
  LZZ_INLINE ParseRecoverOpt::ParseRecoverOpt (StringConstIter str_beg, StringConstIter str_end, basl::ErrorRec & error_rec)
    : str_beg (str_beg), str_end (str_end), error_rec (error_rec)
         {}
}
namespace
{
  ParseRecoverOpt::~ ParseRecoverOpt ()
         {}
}
namespace gram
{
  void parseRecoverOpt (basl::ErrorRec & error_rec)
  {
    util::String const & opt_rec = conf::getOptionValue (conf::opt_rec);
    // remove spaces from string, if empty do nothing
    String str = removeChars (opt_rec, " \t");
    if (! str.empty ())
    {
      ParseRecoverOpt parser (str.begin (), str.end (), error_rec);
      parser.parse ();
    }
  }
}
namespace gram
{
  void printRecoverTokens (std::ostream & os)
  {
    os << "Token names usable in -r option (lexeme follows token name):" << '\n';
    TokenRec const * beg = token_rec_set;
    TokenRec const * end = token_rec_set + sizeof (token_rec_set) / sizeof (token_rec_set [0]);
    std::for_each (beg, end, PrintTokenRecNameAndLexeme (os));
    os << "Token names are not case sensitive." << '\n';
  }
}
namespace gram
{
  void printRecoverHelp (std::ostream & os)
  {
    os << help_text;
  }
}
#undef LZZ_INLINE
