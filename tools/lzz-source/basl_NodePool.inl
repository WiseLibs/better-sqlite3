// basl_NodePool.inl
//

// basil
#include "basl_Node.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE Node * getNode (Node * prev, Token const & token, LRRule const * rule, Node * last_child)
  {
    return getNodePool ().getNode (prev, token, rule, last_child);
  }
}
namespace basl
{
  LZZ_INLINE void recycleNode (Node * node)
  {
    getNodePool ().recycleNode (node);
  }
}
namespace basl
{
  LZZ_INLINE void addNodeRef (Node * node)
  {
    if (node)
    {
      ++ node->num_ref;
    }
  }
}
namespace basl
{
  LZZ_INLINE void remNodeRef (Node * node)
  {
    if (node && -- node->num_ref == 0)
    {
      recycleNode (node);
    }
  }
}
#undef LZZ_INLINE
