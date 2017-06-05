// basl_SyntaxTree.cpp
//

#include "basl_SyntaxTree.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_SyntaxTree.inl"
#endif
// basil
#include "basl_Node.h"
#include "basl_NodePool.h"
#define LZZ_INLINE inline
namespace basl
{
  SyntaxTree::SyntaxTree (Node * node)
    : m_node (node)
    {
      addNodeRef (m_node);
    }
}
namespace basl
{
  SyntaxTree::SyntaxTree (SyntaxTree const & tree)
    : m_node (tree.m_node)
    {
      addNodeRef (m_node);
    }
}
namespace basl
{
  SyntaxTree::~ SyntaxTree ()
    {
      remNodeRef (m_node);
    }
}
namespace basl
{
  SyntaxTree & SyntaxTree::operator = (SyntaxTree const & tree)
    {
      addNodeRef (tree.m_node);
      remNodeRef (m_node);
      m_node = tree.m_node;
      return * this;
    }
}
#undef LZZ_INLINE
