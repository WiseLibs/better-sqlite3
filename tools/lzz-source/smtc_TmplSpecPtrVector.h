// smtc_TmplSpecPtrVector.h
//

#ifndef LZZ_smtc_TmplSpecPtrVector_h
#define LZZ_smtc_TmplSpecPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_TmplSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <TmplSpecPtr> TmplSpecPtrVector;
}
namespace smtc
{
  typedef std::vector <TmplSpecPtr>::iterator TmplSpecPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <TmplSpecPtr>::const_iterator TmplSpecPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <TmplSpecPtr>::reverse_iterator TmplSpecPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <TmplSpecPtr>::const_reverse_iterator TmplSpecPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
