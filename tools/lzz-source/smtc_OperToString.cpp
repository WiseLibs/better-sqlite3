// smtc_OperToString.cpp
//

#include "smtc_OperToString.h"
#define LZZ_INLINE inline
namespace smtc
{
  char const * operToString (OperKind oper)
  {
    char const * str = 0;
    switch (oper)
    {
      case CALL_OPER:
      {
        str = "()";
        break;
      }
      case SUBSCR_OPER:
      {
        str = "[]";
        break;
      }
      case NEW_ARRAY_OPER:
      {
        str = "new []";
        break;
      }
      case DELETE_ARRAY_OPER:
      {
        str = "delete []";
        break;
      }
      case AND_OPER:
      {
        str = "&&";
        break;
      }
      case ASSIGN_OPER:
      {
        str = "=";
        break;
      }
      case BITAND_OPER:
      {
        str = "&";
        break;
      }
      case BITAND_ASSIGN_OPER:
      {
        str = "&=";
        break;
      }
      case BITNOT_OPER:
      {
        str = "~";
        break;
      }
      case BITOR_OPER:
      {
        str = "|";
        break;
      }
      case BITOR_ASSIGN_OPER:
      {
        str = "|=";
        break;
      }
      case COMMA_OPER:
      {
        str = ",";
        break;
      }
      case DEC_OPER:
      {
        str = "--";
        break;
      }
      case DELETE_OPER:
      {
        str = "delete";
        break;
      }
      case DIVIDE_OPER:
      {
        str = "/";
        break;
      }
      case DIVIDE_ASSIGN_OPER:
      {
        str = "/=";
        break;
      }
      case EQ_OPER:
      {
        str = "==";
        break;
      }
      case GT_OPER:
      {
        str = ">";
        break;
      }
      case GTEQ_OPER:
      {
        str = ">=";
        break;
      }
      case INC_OPER:
      {
        str = "++";
        break;
      }
      case LSHIFT_OPER:
      {
        str = "<<";
        break;
      }
      case LSHIFT_ASSIGN_OPER:
      {
        str = "<<=";
        break;
      }
      case LT_OPER:
      {
        str = "<";
        break;
      }
      case LTEQ_OPER:
      {
        str = "<=";
        break;
      }
      case MINUS_OPER:
      {
        str = "-";
        break;
      }
      case MINUS_ASSIGN_OPER:
      {
        str = "-=";
        break;
      }
      case MOD_OPER:
      {
        str = "%";
        break;
      }
      case MOD_ASSIGN_OPER:
      {
        str = "%=";
        break;
      }
      case NEW_OPER:
      {
        str = "new";
        break;
      }
      case NOT_OPER:
      {
        str = "!";
        break;
      }
      case NOTEQ_OPER:
      {
        str = "!=";
        break;
      }
      case OR_OPER:
      {
        str = "||";
        break;
      }
      case PLUS_OPER:
      {
        str = "+";
        break;
      }
      case PLUS_ASSIGN_OPER:
      {
        str = "+=";
        break;
      }
      case PTR_OPER:
      {
        str = "->";
        break;
      }
      case PTR_TIMES_OPER:
      {
        str = "->*";
        break;
      }
      case RSHIFT_OPER:
      {
        str = ">>";
        break;
      }
      case RSHIFT_ASSIGN_OPER:
      {
        str = ">>=";
        break;
      }
      case TIMES_OPER:
      {
        str = "*";
        break;
      }
      case TIMES_ASSIGN_OPER:
      {
        str = "*=";
        break;
      }
      case XOR_OPER:
      {
        str = "^";
        break;
      }
      case XOR_ASSIGN_OPER:
      {
        str = "^=";
        break;
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
