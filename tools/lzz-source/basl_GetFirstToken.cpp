// basl_GetFirstToken.cpp
//

#include "basl_GetFirstToken.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_GetFirstToken.inl"
#endif
// std lib
#include <algorithm>
#include <deque>

// basil
#include "basl_Node.h"
#define LZZ_INLINE inline
namespace basl
{
  Token getFirstToken (Nonterm const & nonterm)
  {
    Token first_token;
    typedef std::pair <Nonterm const *, int> ChildIter;
    std::deque <ChildIter> stack;
    stack.push_back (ChildIter (& nonterm, 1));
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
      }
      else
      {
        Node & node = nonterm.getChild (iter.second ++);
        Token const & token = node.getToken ();
        if (token.isSet ())
        {
          first_token = token;
          break;
        }
        Nonterm const & nonterm = node.getNonterm ();
        if (nonterm.isSet ())
        {
          stack.push_back (ChildIter (& nonterm, 1));
        }
      }
    }
    return first_token;
  }
}
#undef LZZ_INLINE
