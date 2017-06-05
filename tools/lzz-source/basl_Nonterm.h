// basl_Nonterm.h
//

#ifndef LZZ_basl_Nonterm_h
#define LZZ_basl_Nonterm_h
// basil
#include "basl_AttribPtr.h"
#include "basl_Token.h"
#define LZZ_INLINE inline
namespace basl
{
  struct NontermInfo;
}
namespace basl
{
  struct Visitor;
}
namespace basl
{
  struct LRRule;
}
namespace basl
{
  class Node;
}
namespace basl
{
  class NodePool;
}
namespace basl
{
  class Nonterm
  {
    LRRule const * rule;
    Node * last_child;
    AttribPtr attrib;
    friend class NodePool;
  public:
    Nonterm ();
    bool isSet () const;
    void accept (Visitor const & visitor);
    int getNumChild () const;
    Node & getChild (int num) const;
    void visitChildren (Visitor const & visitor);
    LRRule const & getRule () const;
    NontermInfo const * getInfo () const;
    void setAttrib (AttribPtr const & a);
    AttribPtr const & getAttrib () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_Nonterm.inl"
#endif
#endif
