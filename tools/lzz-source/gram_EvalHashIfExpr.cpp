// gram_EvalHashIfExpr.cpp
//

#include "gram_EvalHashIfExpr.h"
// gram
#include "gram_GetIdent.h"
#include "gram_LexPPNumber.h"
#include "gram_LiteralCharToInt.h"
#include "gram_MacroTable.h"
#include "gram_Message.h"
#include "gram_PrepKeywordTable.h"
#include "gram_TokenNumber.h"

// util
#include "util_Exception.h"

#include <stdlib.h>
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  typedef long int ValueType;
}
namespace
{
  struct ExprParser
  {
    util::Ident const & dir_name;
    util::Loc const & eol_loc;
    basl::TokenDequeConstIter beg;
    basl::TokenDequeConstIter end;
    bool parse ();
  private:
    int kind;
    basl::Token token;
    void nextToken ();
    ValueType parseExpr ();
    ValueType parseCondExpr ();
    ValueType parseLogOrExpr ();
    ValueType parseLogAndExpr ();
    ValueType parseInclOrExpr ();
    ValueType parseExclOrExpr ();
    ValueType parseAndExpr ();
    ValueType parseEqExpr ();
    ValueType parseRelExpr ();
    ValueType parseShiftExpr ();
    ValueType parseAddExpr ();
    ValueType parseMulExpr ();
    ValueType parseUnaryExpr ();
    ValueType parsePrimaryExpr ();
    void error ();
  public:
    explicit ExprParser (util::Ident const & dir_name, util::Loc const & eol_loc, basl::TokenDequeConstIter beg, basl::TokenDequeConstIter end);
    ~ ExprParser ();
  };
}
namespace
{
  bool ExprParser::parse ()
    {
      nextToken ();
      ValueType value = parseExpr ();
      if (kind != EOT)
      {
        error ();
      }
      // cout << "#if value: " << value << endl;
      return value != 0;
    }
}
namespace
{
  void ExprParser::nextToken ()
    {
      if (beg == end)
      {
        kind = EOT;
      }
      else
      {
        token = * beg;
        ++ beg;
        kind = token.getNumber ();
        // must lex pp-numers to literal tokens
        if (kind == PP_NUMBER_TOKEN)
        {
          lexPPNumber (token);
          kind = token.getNumber ();
        }
        if (kind == IDENT_TOKEN && isPrepKeyword (token.getLexeme (), kind))
        {
          token.setNumber (kind);
        }
      }
    }
}
namespace
{
  ValueType ExprParser::parseExpr ()
    {
      return parseCondExpr ();
    }
}
namespace
{
  ValueType ExprParser::parseCondExpr ()
    {
      ValueType value = parseLogOrExpr ();
      if (kind == QMARK_TOKEN)
      {
        nextToken ();
        ValueType t_value = parseExpr ();
        if (kind != COLON_TOKEN)
        {
          error ();
        }
        nextToken ();
        ValueType f_value = parseExpr ();
        value = (value != 0) ? t_value : f_value;
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseLogOrExpr ()
    {
      ValueType value = parseLogAndExpr ();
      for (;;)
      {
        if (kind == OR_TOKEN)
        {
          nextToken ();
          value = parseLogAndExpr () != 0 || value != 0;
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseLogAndExpr ()
    {
      ValueType value = parseInclOrExpr ();
      for (;;)
      {
        if (kind == AND_TOKEN)
        {
          nextToken ();
          value = parseInclOrExpr () != 0 && value != 0;
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseInclOrExpr ()
    {
      ValueType value = parseExclOrExpr ();
      for (;;)
      {
        if (kind == BITOR_TOKEN)
        {
          nextToken ();
          value |= parseExclOrExpr ();
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseExclOrExpr ()
    {
      ValueType value = parseAndExpr ();
      for (;;)
      {
        if (kind == XOR_TOKEN)
        {
          nextToken ();
          value ^= parseAndExpr ();
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseAndExpr ()
    {
      ValueType value = parseEqExpr ();
      for (;;)
      {
        if (kind == BITAND_TOKEN)
        {
          nextToken ();
          value = value & parseEqExpr ();
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseEqExpr ()
    {
      ValueType value = parseRelExpr ();
      for (;;)
      {
        if (kind == EQ_TOKEN)
        {
          nextToken ();
          value = value == parseRelExpr ();
        }
        else if (kind == NOTEQ_TOKEN)
        {
          nextToken ();
          value = value != parseRelExpr ();
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseRelExpr ()
    {
      ValueType value = parseShiftExpr ();
      for (;;)
      {
        if (kind == LT_TOKEN)
        {
          nextToken ();
          value = value < parseShiftExpr ();
        }
        else if (kind == GT_TOKEN)
        {
          nextToken ();
          value = value > parseShiftExpr ();
        }
        else if (kind == LTEQ_TOKEN)
        {
          nextToken ();
          value = value <= parseShiftExpr ();
        }
        else if (kind == GTEQ_TOKEN)
        {
          nextToken ();
          value = value >= parseShiftExpr ();
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseShiftExpr ()
    {
      ValueType value = parseAddExpr ();
      for (;;)
      {
        if (kind == LSHIFT_TOKEN)
        {
          nextToken ();
          value <<= parseAddExpr ();
        }
        else if (kind == RSHIFT_TOKEN)
        {
          nextToken ();
          value >>= parseAddExpr ();
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseAddExpr ()
    {
      ValueType value = parseMulExpr ();
      for (;;)
      {
        if (kind == PLUS_TOKEN)
        {
          nextToken ();
          value += parseMulExpr ();
        }
        else if (kind == MINUS_TOKEN)
        {
          nextToken ();
          value -= parseMulExpr ();
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseMulExpr ()
    {
      ValueType value = parseUnaryExpr ();
      for (;;)
      {
        if (kind == TIMES_TOKEN)
        {
          nextToken ();
          value *= parseUnaryExpr ();
        }
        else if (kind == DIVIDE_TOKEN || kind == MOD_TOKEN)
        {
          bool is_divide = kind == DIVIDE_TOKEN;
          util::Loc const & op_loc = token.getLoc ();
          nextToken ();
          ValueType divisor = parseUnaryExpr ();
          if (divisor == 0)
          {
            msg::hashIfDivideByZero (op_loc, dir_name);
            throw util::Exception ();
          }
          value = is_divide ? value / divisor : value % divisor;
        }
        else
        {
          break;
        }
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parseUnaryExpr ()
    {
      ValueType value;
      if (kind == PLUS_TOKEN)
      {
        nextToken ();
        value = + parseUnaryExpr ();
      }
      else if (kind == MINUS_TOKEN)
      {
        nextToken ();
        value = - parseUnaryExpr ();
      }
      else if (kind == NOT_TOKEN)
      {
        nextToken ();
        value = ! parseUnaryExpr ();
      }
      else if (kind == BITNOT_TOKEN)
      {
        nextToken ();
        value = ~ parseUnaryExpr ();
      }
      else if (kind == IDENT_TOKEN && token.getLexeme () == defined_ident)
      {
        nextToken ();
        if (kind == IDENT_TOKEN)
        {
          value = isMacro (token.getLexeme ()) ? 1 : 0;
          nextToken ();
        }
        else if (kind == LPAREN_TOKEN)
        {
          nextToken ();
          if (kind == IDENT_TOKEN)
          {
            value = isMacro (token.getLexeme ()) ? 1 : 0;
            nextToken ();
            if (kind == RPAREN_TOKEN)
            {
              nextToken ();
            }
            else
            {
              // syntax error, but OK to continue
              msg::missingHashIfDefinedRightParen (token.getLoc (), dir_name);
            }
          }
          else
          {
            // syntax error
            msg::missingHashIfDefinedIdent (token.getLoc (), dir_name);
            throw util::Exception ();
          }
        }
        else
        {
          // syntax error
          msg::missingHashIfDefinedIdent (token.getLoc (), dir_name);
          throw util::Exception ();
        }
      }
      else
      {
        value = parsePrimaryExpr ();
      }
      return value;
    }
}
namespace
{
  ValueType ExprParser::parsePrimaryExpr ()
    {
      ValueType value;
      if (kind == LPAREN_TOKEN)
      {
        nextToken ();
        value = parseExpr ();
        if (kind == RPAREN_TOKEN)
        {
          nextToken ();
        }
        else
        {
          error ();
        }
      }
      else if (kind == LITERAL_INT_TOKEN || kind == ZERO_TOKEN)
      {
        value = strtol (token.getLexeme ().c_str (), 0, 0);
        nextToken ();
      }
      else if (kind == LITERAL_CHAR_TOKEN)
      {
        value = literalCharToInt (token.getLoc (), token.getLexeme ());
        nextToken ();
      }
      else if (kind == LITERAL_FLOAT_TOKEN)
      {
        // read integer part
        value = strtol (token.getLexeme ().c_str (), 0, 0);
        nextToken ();
      }
      else if (kind == IDENT_TOKEN)
      {
        if (token.getLexeme () == true_ident)
        {
          value = 1;
        }
        else
        {
          value = 0;
        }
        nextToken ();
      }
      else
      {
        error ();
      }
      return value;
    }
}
namespace
{
  void ExprParser::error ()
    {
      // issue message and abort
      if (kind == EOT)
      {
        msg::hashIfSyntaxErrorAtEol (eol_loc, dir_name);
      }
      else
      {
        msg::hashIfSyntaxErrorBeforeToken (token.getLoc (), dir_name, token.getLexeme ());
      }
      throw util::Exception ();
    }
}
namespace
{
  LZZ_INLINE ExprParser::ExprParser (util::Ident const & dir_name, util::Loc const & eol_loc, basl::TokenDequeConstIter beg, basl::TokenDequeConstIter end)
    : dir_name (dir_name), eol_loc (eol_loc), beg (beg), end (end)
         {}
}
namespace
{
  ExprParser::~ ExprParser ()
         {}
}
namespace gram
{
  bool evalHashIfExpr (util::Ident const & dir_name, util::Loc const & eol_loc, basl::TokenDeque const & in_set)
  {
    ExprParser parser (dir_name, eol_loc, in_set.begin (), in_set.end ());
    return parser.parse ();
  }
}
#undef LZZ_INLINE
