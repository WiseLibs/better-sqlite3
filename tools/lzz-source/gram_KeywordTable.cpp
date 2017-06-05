// gram_KeywordTable.cpp
//

#include "gram_KeywordTable.h"
// gram
#include "gram_TokenNumber.h"

// util
#include "util_GetIdent.h"
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
  struct KeywordData
  {
    IntDataTable data_table;
    KeywordData ();
    bool isKeyword (Ident const & lexeme, int & kind) const;
  };
}
namespace
{
  KeywordData const & getKeywordData ();
}
namespace
{
  KeywordData::KeywordData ()
    {
      // populate database
      struct
      {
        char const * name;
        int kind;
      }
      database [] =
      {
        { "_dinit",     DINIT_TOKEN },
        { "_dll_api",   DLL_API_TOKEN },
        { "auto",       AUTO_TOKEN },
        { "bool",       BOOL_TOKEN },
        { "catch",      CATCH_TOKEN },
        { "char",       CHAR_TOKEN },
        { "class",      CLASS_TOKEN },
        { "const",      CONST_TOKEN },
        { "delete",     DELETE_TOKEN },
        { "double",     DOUBLE_TOKEN },
        { "enum",       ENUM_TOKEN },
        { "explicit",   EXPLICIT_TOKEN },
        { "extern",     EXTERN_TOKEN },
        { "float",      FLOAT_TOKEN },
        { "friend",     FRIEND_TOKEN },
        { "inline",     INLINE_TOKEN },
        { "int",        INT_TOKEN },
        { "long",       LONG_TOKEN },
        { "mutable",    MUTABLE_TOKEN },
        { "namespace",  NAMESPACE_TOKEN },
        { "new",        NEW_TOKEN },
        { "operator",   OPERATOR_TOKEN },
        { "private",    PRIVATE_TOKEN },
        { "protected",  PROTECTED_TOKEN },
        { "public",     PUBLIC_TOKEN },
        { "register",   REGISTER_TOKEN },
        { "short",      SHORT_TOKEN },
        { "signed",     SIGNED_TOKEN },
        { "static",     STATIC_TOKEN },
        { "struct",     STRUCT_TOKEN },
        { "template",   TEMPLATE_TOKEN },
        { "throw",      THROW_TOKEN },
        { "try",        TRY_TOKEN },
        { "typedef",    TYPEDEF_TOKEN },
        { "typename",   TYPENAME_TOKEN },
        { "union",      UNION_TOKEN },
        { "unsigned",   UNSIGNED_TOKEN },
        { "using",      USING_TOKEN },
        { "virtual",    VIRTUAL_TOKEN },
        { "void",       VOID_TOKEN },
        { "volatile",   VOLATILE_TOKEN },
        { "wchar_t",    WCHAR_TOKEN },

#ifdef PRL_BUILD
        // prl extensions
        { "return",     RETURN_TOKEN },
        { "navigator",  NAVIGATOR_TOKEN },
        { "vdf",        VDF_TOKEN },
#endif
      };
      for (int i = 0; i < sizeof (database) / sizeof (database [0]); ++ i)
      {
        data_table.addData (util::getIdent (database [i].name).getHandle (), database [i].kind);
      }
    }
}
namespace
{
  bool KeywordData::isKeyword (Ident const & lexeme, int & kind) const
    {
      bool result = false;
      IntDataTableFindResult find_result = data_table.findData (lexeme.getHandle ());
      if (find_result.hasData ())
      {
        kind = find_result.getData ();
        result = true;
      }
      return result;
    }
}
namespace
{
  KeywordData const & getKeywordData ()
  {
    static KeywordData data;
    return data;
  }
}
namespace gram
{
  bool isKeyword (util::Ident const & lexeme, int & kind)
  {
    return getKeywordData ().isKeyword (lexeme, kind);
  }
}
#undef LZZ_INLINE
