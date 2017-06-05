// smtc_MbrInitPtrVector.h
//

#ifndef LZZ_smtc_MbrInitPtrVector_h
#define LZZ_smtc_MbrInitPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_MbrInitPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <MbrInitPtr> MbrInitPtrVector;
}
namespace smtc
{
  typedef std::vector <MbrInitPtr>::iterator MbrInitPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <MbrInitPtr>::const_iterator MbrInitPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <MbrInitPtr>::reverse_iterator MbrInitPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <MbrInitPtr>::const_reverse_iterator MbrInitPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
