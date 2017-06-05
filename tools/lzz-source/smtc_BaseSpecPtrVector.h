// smtc_BaseSpecPtrVector.h
//

#ifndef LZZ_smtc_BaseSpecPtrVector_h
#define LZZ_smtc_BaseSpecPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_BaseSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <BaseSpecPtr> BaseSpecPtrVector;
}
namespace smtc
{
  typedef std::vector <BaseSpecPtr>::iterator BaseSpecPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <BaseSpecPtr>::const_iterator BaseSpecPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <BaseSpecPtr>::reverse_iterator BaseSpecPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <BaseSpecPtr>::const_reverse_iterator BaseSpecPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
