// basl_Node.h
//

#ifndef LZZ_basl_Node_h
#define LZZ_basl_Node_h
// basil
#include "basl_Nonterm.h"
#include "basl_Token.h"
#define LZZ_INLINE inline
namespace basl
{
  class Node
  {
    Nonterm nonterm;
    Token token;
    Node * prev;
    int num_ref;
    friend class NodePool;
    friend void addNodeRef (Node * node);
    friend void remNodeRef (Node * node);
  public:
    Node ();
    ~ Node ();
    Token & getToken ();
    Nonterm & getNonterm ();
    Node * getPrev (int n);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_Node.inl"
#endif
#endif
