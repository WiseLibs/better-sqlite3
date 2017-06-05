// smtc_EnumtorPtrVector.h
//

#ifndef LZZ_smtc_EnumtorPtrVector_h
#define LZZ_smtc_EnumtorPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_EnumtorPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <EnumtorPtr> EnumtorPtrVector;
}
namespace smtc
{
  typedef std::vector <EnumtorPtr>::iterator EnumtorPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <EnumtorPtr>::const_iterator EnumtorPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <EnumtorPtr>::reverse_iterator EnumtorPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <EnumtorPtr>::const_reverse_iterator EnumtorPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
