// basl_PrintSyntaxTree.h
//

#ifndef LZZ_basl_PrintSyntaxTree_h
#define LZZ_basl_PrintSyntaxTree_h
// std lib
#include <iostream>
#define LZZ_INLINE inline
namespace basl
{
  class Node;
}
namespace basl
{
  class Nonterm;
}
namespace basl
{
  void printSyntaxTree (std::ostream & os, Node & node);
}
namespace basl
{
  void printSyntaxTree (std::ostream & os, Nonterm const & nonterm);
}
#undef LZZ_INLINE
#endif
