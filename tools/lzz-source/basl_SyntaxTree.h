// basl_SyntaxTree.h
//

#ifndef LZZ_basl_SyntaxTree_h
#define LZZ_basl_SyntaxTree_h
#define LZZ_INLINE inline
namespace basl
{
  struct Node;
}
namespace basl
{
  class SyntaxTree
  {
    Node * m_node;
  public:
    SyntaxTree (Node * node = 0);
    SyntaxTree (SyntaxTree const & tree);
    ~ SyntaxTree ();
    SyntaxTree & operator = (SyntaxTree const & tree);
    bool isEmpty () const;
    Node & getNode () const;
    Node * pointer () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_SyntaxTree.inl"
#endif
#endif
