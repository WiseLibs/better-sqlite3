// smtc_NsPtrVector.h
//

#ifndef LZZ_smtc_NsPtrVector_h
#define LZZ_smtc_NsPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_NsPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <NsPtr> NsPtrVector;
}
namespace smtc
{
  typedef std::vector <NsPtr>::iterator NsPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <NsPtr>::const_iterator NsPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <NsPtr>::reverse_iterator NsPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <NsPtr>::const_reverse_iterator NsPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
