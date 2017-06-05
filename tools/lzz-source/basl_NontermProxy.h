// basl_NontermProxy.h
//

#ifndef LZZ_basl_NontermProxy_h
#define LZZ_basl_NontermProxy_h
// basil
#include "basl_AttribPtr.h"
#define LZZ_INLINE inline
namespace basl
{
  class Token;
}
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
  struct NontermInfo;
}
namespace basl
{
  struct LRRule;
}
namespace basl
{
  struct Visitor;
}
namespace basl
{
  class NontermProxy
  {
    Nonterm & m_nonterm;
  public:
    NontermProxy (Nonterm & nonterm);
    void accept (Visitor const & visitor);
    void visitChildren (Visitor const & visitor);
    int getNumChild () const;
    Node & getChild (int num) const;
    LRRule const & getRule () const;
    NontermInfo const * getInfo () const;
    void setAttrib (AttribPtr const & a);
    AttribPtr const & getAttrib () const;
    operator Nonterm & () const;
    Nonterm * operator & () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_NontermProxy.inl"
#endif
#endif
