// gram_MacroArgPtrVector.h
//

#ifndef LZZ_gram_MacroArgPtrVector_h
#define LZZ_gram_MacroArgPtrVector_h
// std lib
#include <vector>

// gram
#include "gram_MacroArgPtr.h"
#define LZZ_INLINE inline
namespace gram
{
  typedef std::vector <MacroArgPtr> MacroArgPtrVector;
}
namespace gram
{
  typedef std::vector <MacroArgPtr>::iterator MacroArgPtrVectorIter;
}
namespace gram
{
  typedef std::vector <MacroArgPtr>::const_iterator MacroArgPtrVectorConstIter;
}
namespace gram
{
  typedef std::vector <MacroArgPtr>::reverse_iterator MacroArgPtrVectorRevIter;
}
namespace gram
{
  typedef std::vector <MacroArgPtr>::const_reverse_iterator MacroArgPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
