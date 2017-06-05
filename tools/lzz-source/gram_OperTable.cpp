// gram_OperTable.cpp
//

#include "gram_OperTable.h"
// gram
#include "gram_TokenNumber.h"

// util
#include "util_GetIdent.h"
#include "util_IntDataTable.h"
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
  struct OperTable
  {
    IntDataTable data_table;
    OperTable ();
    int getOperKind (Ident const & name);
  };
}
namespace
{
  OperTable::OperTable ()
    {
      // populate table
      struct
      {
        char const * name;
        int kind;
      }
      database [] =
      {
        { "!",      NOT_TOKEN },
        { "!=",     NOTEQ_TOKEN }, 
        { "#",      HASH_TOKEN },
        { "##",     DBLHASH_TOKEN },
        { "$",      DOLLAR_TOKEN },
        { "%",      MOD_TOKEN },
        { "%=",     MOD_ASSIGN_TOKEN },
        { "&",      BITAND_TOKEN }, 
        { "&&",     AND_TOKEN }, 
        { "&=",     BITAND_ASSIGN_TOKEN }, 
        { "(",      LPAREN_TOKEN },
        { ")",      RPAREN_TOKEN },
        { "*",      TIMES_TOKEN },
        { "*=",     TIMES_ASSIGN_TOKEN },
        { "+",      PLUS_TOKEN },
        { "++",     INC_TOKEN },
        { "+=",     PLUS_ASSIGN_TOKEN },
        { ",",      COMMA_TOKEN },
        { "-",      MINUS_TOKEN },
        { "--",     DEC_TOKEN },
        { "-=",     MINUS_ASSIGN_TOKEN },
        { "->",     PTR_TOKEN },
        { "->*",    PTR_TIMES_TOKEN },
        { ".",      DOT_TOKEN },
        { ".*",     DOT_TIMES_TOKEN },
        { "...",    ELLIPSE_TOKEN },
        { "/",      DIVIDE_TOKEN },
        { "/=",     DIVIDE_ASSIGN_TOKEN },
        { ":",      COLON_TOKEN },
        { "::",     DCOLON_TOKEN },
        { ";",      SEMI_TOKEN }, 
        { "<",      LT_TOKEN }, 
        { "<<",     LSHIFT_TOKEN },
        { "<<=",    LSHIFT_ASSIGN_TOKEN },
        { "<=",     LTEQ_TOKEN },
        { "=",      ASSIGN_TOKEN },
        { "==",     EQ_TOKEN }, 
        { ">",      GT_TOKEN }, 
        { ">=",     GTEQ_TOKEN },
        { ">>",     RSHIFT_TOKEN },
        { ">>=",    RSHIFT_ASSIGN_TOKEN },
        { "?",      QMARK_TOKEN },
        { "[",      LBRACK_TOKEN },
        { "]",      RBRACK_TOKEN },
        { "^",      XOR_TOKEN },
        { "^=",     XOR_ASSIGN_TOKEN },
        { "{",      LBRACE_TOKEN },
        { "|",      BITOR_TOKEN }, 
        { "|=",     BITOR_ASSIGN_TOKEN }, 
        { "||",     OR_TOKEN }, 
        { "}",      RBRACE_TOKEN },
        { "~",      BITNOT_TOKEN },
        // digraphs
        { "<%",     LBRACE_TOKEN },
        { "%>",     RBRACE_TOKEN },
        { "<:",     LBRACK_TOKEN },
        { ":>",     RBRACK_TOKEN },
        { "%:",     HASH_TOKEN },
        { "%:%:",   DBLHASH_TOKEN },
      };
      for (int i = 0; i < sizeof (database) / sizeof (database [0]); ++ i)
      {
        data_table.addData (util::getIdent (database [i].name).getHandle (), database [i].kind);
      }
    }
}
namespace
{
  int OperTable::getOperKind (Ident const & name)
    {
      // find keyword
      return data_table.findData (name.getHandle ()).getData ();
    }
}
namespace gram
{
  int getOperKind (util::Ident const & name)
  {
    static OperTable oper_table;
    return oper_table.getOperKind (name);
  }
}
#undef LZZ_INLINE
