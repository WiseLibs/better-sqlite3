// smtc_LazyBaseSpecPtrVector.h
//

#ifndef LZZ_smtc_LazyBaseSpecPtrVector_h
#define LZZ_smtc_LazyBaseSpecPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_LazyBaseSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <LazyBaseSpecPtr> LazyBaseSpecPtrVector;
}
namespace smtc
{
  typedef std::vector <LazyBaseSpecPtr>::iterator LazyBaseSpecPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <LazyBaseSpecPtr>::const_iterator LazyBaseSpecPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <LazyBaseSpecPtr>::reverse_iterator LazyBaseSpecPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <LazyBaseSpecPtr>::const_reverse_iterator LazyBaseSpecPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
