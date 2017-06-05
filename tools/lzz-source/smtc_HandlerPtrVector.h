// smtc_HandlerPtrVector.h
//

#ifndef LZZ_smtc_HandlerPtrVector_h
#define LZZ_smtc_HandlerPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_HandlerPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <HandlerPtr> HandlerPtrVector;
}
namespace smtc
{
  typedef std::vector <HandlerPtr>::iterator HandlerPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <HandlerPtr>::const_iterator HandlerPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <HandlerPtr>::reverse_iterator HandlerPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <HandlerPtr>::const_reverse_iterator HandlerPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
