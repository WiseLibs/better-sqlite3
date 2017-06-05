// basl_Nonterm.cpp
//

#include "basl_Nonterm.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_Nonterm.inl"
#endif
// basil
#include "basl_LRData.h"
#include "basl_Node.h"
#define LZZ_INLINE inline
namespace basl
{
  Node & Nonterm::getChild (int num) const
    {
      return * last_child->getPrev (rule->size - num);
    }
}
namespace basl
{
  void Nonterm::visitChildren (Visitor const & visitor)
    {
      int n = rule->size;
      for (int i = 1; i <= n; ++ i)
      {
        Nonterm & nonterm = last_child->getPrev (n - i)->getNonterm ();
        if (nonterm.isSet ())
        {
          nonterm.accept (visitor);
        }
      }
    }
}
#undef LZZ_INLINE
