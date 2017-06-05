// basl_NodePool.h
//

#ifndef LZZ_basl_NodePool_h
#define LZZ_basl_NodePool_h
#define LZZ_INLINE inline
namespace basl
{
  struct Node;
}
namespace basl
{
  struct Nonterm;
}
namespace basl
{
  struct LRRule;
}
namespace basl
{
  struct Token;
}
namespace basl
{
  class NodePool
  {
    Node * m_recycled_node;
  public:
    NodePool ();
    ~ NodePool ();
    Node * getNode (Node * prev, Token const & token, LRRule const * rule, Node * last_child);
    void recycleNode (Node * node);
  };
}
namespace basl
{
  NodePool & getNodePool ();
}
namespace basl
{
  Node * getNode (Node * prev, Token const & token, LRRule const * rule, Node * last_child);
}
namespace basl
{
  void recycleNode (Node * node);
}
namespace basl
{
  void addNodeRef (Node * node);
}
namespace basl
{
  void remNodeRef (Node * node);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_NodePool.inl"
#endif
#endif
