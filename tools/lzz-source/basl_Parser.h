// basl_Parser.h
//

#ifndef LZZ_basl_Parser_h
#define LZZ_basl_Parser_h
#define LZZ_INLINE inline
namespace basl
{
  class Nonterm;
}
namespace basl
{
  class Parser
  {
  public:
    virtual ~ Parser ();
    virtual bool onNode (Nonterm & nonterm) = 0;
  };
}
#undef LZZ_INLINE
#endif
