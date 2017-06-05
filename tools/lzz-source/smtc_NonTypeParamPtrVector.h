// smtc_NonTypeParamPtrVector.h
//

#ifndef LZZ_smtc_NonTypeParamPtrVector_h
#define LZZ_smtc_NonTypeParamPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_NonTypeParamPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <NonTypeParamPtr> NonTypeParamPtrVector;
}
namespace smtc
{
  typedef std::vector <NonTypeParamPtr>::iterator NonTypeParamPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <NonTypeParamPtr>::const_iterator NonTypeParamPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <NonTypeParamPtr>::reverse_iterator NonTypeParamPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <NonTypeParamPtr>::const_reverse_iterator NonTypeParamPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
