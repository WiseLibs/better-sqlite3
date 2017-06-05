// basl_PrintSyntaxTree.cpp
//

#include "basl_PrintSyntaxTree.h"
// std lib
#include <deque>

// basl
#include "basl_LRData.h"
#include "basl_Node.h"
#include "basl_Nonterm.h"
#include "basl_NontermInfo.h"

// util
#include "util_IdentToString.h"
#define LZZ_INLINE inline
namespace basl
{
  void printSyntaxTree (std::ostream & os, Node & node)
  {
    Token const & token = node.getToken ();
    if (token.isSet ())
    {
      os << identToString (token.getLexeme ()) << '\n';
    }
    Nonterm const & nonterm = node.getNonterm ();
    if (nonterm.isSet ())
    {
      printSyntaxTree (os, nonterm);
    }
  }
}
namespace basl
{
  void printSyntaxTree (std::ostream & os, Nonterm const & nonterm)
  {
    LRRule const & rule = nonterm.getRule ();
    os << rule.str;
    // info->name is node name
    NontermInfo const * info = rule.nonterm_info;
    os << " [" << info->name << "]";
    os << '\n';
    typedef std::pair <Nonterm const *, int> ChildIter;
    std::deque <ChildIter> stack;
    stack.push_back (ChildIter (& nonterm, 1));
    int indent = 1;
    for (;;)
    {
      ChildIter & iter = stack.back ();
      Nonterm const & nonterm = * iter.first;
      if (iter.second > nonterm.getNumChild ())
      {
        stack.pop_back ();
        if (stack.empty ())
        {
          break;
        }
        -- indent;
      }
      else
      {
        Node & node = nonterm.getChild (iter.second ++);
        Token const & token = node.getToken ();
        if (token.isSet ())
        {
          os.width (indent * 2);
          os << "";
          os << identToString (token.getLexeme ()) << '\n';
        }
        Nonterm const & nonterm = node.getNonterm ();
        if (nonterm.isSet ())
        {
          LRRule const & rule = nonterm.getRule ();
          os.width (indent * 2);
          os << "";
          os << rule.str;
          // info->name is node name
          NontermInfo const * info = rule.nonterm_info;
          os << " [" << info->name << "]";
          os << '\n';
          stack.push_back (ChildIter (& nonterm, 1));
          ++ indent;
        }
      }
    }
  }
}
#undef LZZ_INLINE
