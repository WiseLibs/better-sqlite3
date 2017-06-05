// gram_FileStatPtrVector.h
//

#ifndef LZZ_gram_FileStatPtrVector_h
#define LZZ_gram_FileStatPtrVector_h
// std lib
#include <vector>

// gram
#include "gram_FileStatPtr.h"
#define LZZ_INLINE inline
namespace gram
{
  typedef std::vector <FileStatPtr> FileStatPtrVector;
}
namespace gram
{
  typedef std::vector <FileStatPtr>::iterator FileStatPtrVectorIter;
}
namespace gram
{
  typedef std::vector <FileStatPtr>::const_iterator FileStatPtrVectorConstIter;
}
namespace gram
{
  typedef std::vector <FileStatPtr>::reverse_iterator FileStatPtrVectorRevIter;
}
namespace gram
{
  typedef std::vector <FileStatPtr>::const_reverse_iterator FileStatPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
