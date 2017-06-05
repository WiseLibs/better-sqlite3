// basl_NodePool.cpp
//

#include "basl_NodePool.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_NodePool.inl"
#endif
// basil
#include "basl_Node.h"
#define LZZ_INLINE inline
namespace basl
{
  NodePool::NodePool ()
    : m_recycled_node (0)
    {}
}
namespace basl
{
  NodePool::~ NodePool ()
    {
      // free nodes
      while (m_recycled_node)
      {
        Node * node = m_recycled_node;
        m_recycled_node = node->prev;
        delete node;
      }
    }
}
namespace basl
{
  Node * NodePool::getNode (Node * prev, Token const & token, LRRule const * rule, Node * last_child)
    {
      Node * node;
      if (m_recycled_node)
      {
        node = m_recycled_node;
        m_recycled_node = node->prev;
      }
      else
      {
        node = new Node ();
      }
      if (last_child)
      {
        ++ last_child->num_ref;
      }
      node->prev = prev;
      node->nonterm.last_child = last_child;
      node->token = token;
      node->nonterm.rule = rule;
      node->num_ref = 0;
      return node;
    }
}
namespace basl
{
  void NodePool::recycleNode (Node * node)
    {
      for (;;)
      {
        Node * next_node = 0;
        if (node->nonterm.last_child && -- node->nonterm.last_child->num_ref == 0)
        {
          next_node = node->nonterm.last_child;
        }
        node->prev = m_recycled_node;
        m_recycled_node = node;
        if (! next_node)
        {
          break;
        }
        node = next_node;
      }
    }
}
namespace basl
{
  NodePool & getNodePool ()
  {
    static NodePool node_pool;
    return node_pool;
  }
}
#undef LZZ_INLINE
