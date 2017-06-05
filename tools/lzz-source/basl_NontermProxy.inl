// basl_NontermProxy.inl
//

// basil
#include "basl_Nonterm.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE NontermProxy::NontermProxy (Nonterm & nonterm)
    : m_nonterm (nonterm)
    {}
}
namespace basl
{
  LZZ_INLINE void NontermProxy::accept (Visitor const & visitor)
    {
      m_nonterm.accept (visitor);
    }
}
namespace basl
{
  LZZ_INLINE void NontermProxy::visitChildren (Visitor const & visitor)
    {
      m_nonterm.visitChildren (visitor);
    }
}
namespace basl
{
  LZZ_INLINE int NontermProxy::getNumChild () const
    {
      return m_nonterm.getNumChild ();
    }
}
namespace basl
{
  LZZ_INLINE Node & NontermProxy::getChild (int num) const
    {
      return m_nonterm.getChild (num);
    }
}
namespace basl
{
  LZZ_INLINE LRRule const & NontermProxy::getRule () const
    {
      return m_nonterm.getRule ();
    }
}
namespace basl
{
  LZZ_INLINE NontermInfo const * NontermProxy::getInfo () const
    {
      return m_nonterm.getInfo ();
    }
}
namespace basl
{
  LZZ_INLINE void NontermProxy::setAttrib (AttribPtr const & a)
    {
      m_nonterm.setAttrib (a);
    }
}
namespace basl
{
  LZZ_INLINE AttribPtr const & NontermProxy::getAttrib () const
    {
      return m_nonterm.getAttrib ();
    }
}
namespace basl
{
  LZZ_INLINE NontermProxy::operator Nonterm & () const
    {
      return m_nonterm;
    }
}
namespace basl
{
  LZZ_INLINE Nonterm * NontermProxy::operator & () const
    {
      return & m_nonterm;
    }
}
#undef LZZ_INLINE
