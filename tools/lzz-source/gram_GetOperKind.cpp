// gram_GetOperKind.cpp
//

#include "gram_GetOperKind.h"
// gram
#include "gram_TokenNumber.h"
#define LZZ_INLINE inline
namespace gram
{
  smtc::OperKind getOperKind (int number)
  {
    smtc::OperKind kind;
    switch (number)
    {
      case AND_TOKEN:
      {
        kind = smtc::AND_OPER;
        break;
      }
      case ASSIGN_TOKEN:
      {
        kind = smtc::ASSIGN_OPER;
        break;
      }
      case BITAND_TOKEN:
      {
        kind = smtc::BITAND_OPER;
        break;
      }
      case BITAND_ASSIGN_TOKEN:
      {
        kind = smtc::BITAND_ASSIGN_OPER;
        break;
      }
      case BITNOT_TOKEN:
      {
        kind = smtc::BITNOT_OPER;
        break;
      }
      case BITOR_TOKEN:
      {
        kind = smtc::BITOR_OPER;
        break;
      }
      case BITOR_ASSIGN_TOKEN:
      {
        kind = smtc::BITOR_ASSIGN_OPER;
        break;
      }
      case COMMA_TOKEN:
      {
        kind = smtc::COMMA_OPER;
        break;
      }
      case DEC_TOKEN:
      {
        kind = smtc::DEC_OPER;
        break;
      }
      case DELETE_TOKEN:
      {
        kind = smtc::DELETE_OPER;
        break;
      }
      case DIVIDE_TOKEN:
      {
        kind = smtc::DIVIDE_OPER;
        break;
      }
      case DIVIDE_ASSIGN_TOKEN:
      {
        kind = smtc::DIVIDE_ASSIGN_OPER;
        break;
      }
      case EQ_TOKEN:
      {
        kind = smtc::EQ_OPER;
        break;
      }
      case GT_TOKEN:
      {
        kind = smtc::GT_OPER;
        break;
      }
      case GTEQ_TOKEN:
      {
        kind = smtc::GTEQ_OPER;
        break;
      }
      case INC_TOKEN:
      {
        kind = smtc::INC_OPER;
        break;
      }
      case LSHIFT_TOKEN:
      {
        kind = smtc::LSHIFT_OPER;
        break;
      }
      case LSHIFT_ASSIGN_TOKEN:
      {
        kind = smtc::LSHIFT_ASSIGN_OPER;
        break;
      }
      case LT_TOKEN:
      {
        kind = smtc::LT_OPER;
        break;
      }
      case LTEQ_TOKEN:
      {
        kind = smtc::LTEQ_OPER;
        break;
      }
      case MINUS_TOKEN:
      {
        kind = smtc::MINUS_OPER;
        break;
      }
      case MINUS_ASSIGN_TOKEN:
      {
        kind = smtc::MINUS_ASSIGN_OPER;
        break;
      }
      case MOD_TOKEN:
      {
        kind = smtc::MOD_OPER;
        break;
      }
      case MOD_ASSIGN_TOKEN:
      {
        kind = smtc::MOD_ASSIGN_OPER;
        break;
      }
      case NEW_TOKEN:
      {
        kind = smtc::NEW_OPER;
        break;
      }
      case NOT_TOKEN:
      {
        kind = smtc::NOT_OPER;
        break;
      }
      case NOTEQ_TOKEN:
      {
        kind = smtc::NOTEQ_OPER;
        break;
      }
      case OR_TOKEN:
      {
        kind = smtc::OR_OPER;
        break;
      }
      case PLUS_TOKEN:
      {
        kind = smtc::PLUS_OPER;
        break;
      }
      case PLUS_ASSIGN_TOKEN:
      {
        kind = smtc::PLUS_ASSIGN_OPER;
        break;
      }
      case PTR_TOKEN:
      {
        kind = smtc::PTR_OPER;
        break;
      }
      case PTR_TIMES_TOKEN:
      {
        kind = smtc::PTR_TIMES_OPER;
        break;
      }
      case RSHIFT_TOKEN:
      {
        kind = smtc::RSHIFT_OPER;
        break;
      }
      case RSHIFT_ASSIGN_TOKEN:
      {
        kind = smtc::RSHIFT_ASSIGN_OPER;
        break;
      }
      case TIMES_TOKEN:
      {
        kind = smtc::TIMES_OPER;
        break;
      }
      case TIMES_ASSIGN_TOKEN:
      {
        kind = smtc::TIMES_ASSIGN_OPER;
        break;
      }
      case XOR_TOKEN:
      {
        kind = smtc::XOR_OPER;
        break;
      }
      case XOR_ASSIGN_TOKEN:
      {
        kind = smtc::XOR_ASSIGN_OPER;
        break;
      }
    }
    return kind;
  }
}
#undef LZZ_INLINE
