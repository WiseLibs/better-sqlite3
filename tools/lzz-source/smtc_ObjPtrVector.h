// smtc_ObjPtrVector.h
//

#ifndef LZZ_smtc_ObjPtrVector_h
#define LZZ_smtc_ObjPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_ObjPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <ObjPtr> ObjPtrVector;
}
namespace smtc
{
  typedef std::vector <ObjPtr>::iterator ObjPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <ObjPtr>::const_iterator ObjPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <ObjPtr>::reverse_iterator ObjPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <ObjPtr>::const_reverse_iterator ObjPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
