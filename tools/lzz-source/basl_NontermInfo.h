// basl_NontermInfo.h
//

#ifndef LZZ_basl_NontermInfo_h
#define LZZ_basl_NontermInfo_h
#define LZZ_INLINE inline
namespace basl
{
  class Nonterm;
}
namespace basl
{
  struct Visitor;
}
namespace basl
{
  struct NontermInfo
  {
    char const * name;
    void (* accept) (Nonterm &, Visitor const &);
  };
}
#undef LZZ_INLINE
#endif
