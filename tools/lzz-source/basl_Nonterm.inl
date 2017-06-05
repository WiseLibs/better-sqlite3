// basl_Nonterm.inl
//

// basil
#include "basl_LRData.h"
#include "basl_NontermInfo.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE Nonterm::Nonterm ()
    {}
}
namespace basl
{
  LZZ_INLINE bool Nonterm::isSet () const
    {
      return rule != 0;
    }
}
namespace basl
{
  LZZ_INLINE void Nonterm::accept (Visitor const & visitor)
    {
      // accept visitor only if rule is set
      if (rule)
      {
        rule->nonterm_info->accept (* this, visitor);
      }
    }
}
namespace basl
{
  LZZ_INLINE int Nonterm::getNumChild () const
    {
      return rule->size;
    }
}
namespace basl
{
  LZZ_INLINE LRRule const & Nonterm::getRule () const
    {
      return * rule;
    }
}
namespace basl
{
  LZZ_INLINE NontermInfo const * Nonterm::getInfo () const
    {
      return rule->nonterm_info;
    }
}
namespace basl
{
  LZZ_INLINE void Nonterm::setAttrib (AttribPtr const & a)
    {
      attrib = a;
    }
}
namespace basl
{
  LZZ_INLINE AttribPtr const & Nonterm::getAttrib () const
    {
      return attrib;
    }
}
#undef LZZ_INLINE
