// basl_Node.cpp
//

#include "basl_Node.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_Node.inl"
#endif
#define LZZ_INLINE inline
namespace basl
{
  Node::~ Node ()
    {}
}
namespace basl
{
  Node * Node::getPrev (int n)
    {
      Node * node = this;
      for (; n > 0; -- n)
      {
        node = node->prev;
      }
      return node;
    }
}
#undef LZZ_INLINE
