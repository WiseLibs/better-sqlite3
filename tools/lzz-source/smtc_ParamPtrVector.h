// smtc_ParamPtrVector.h
//

#ifndef LZZ_smtc_ParamPtrVector_h
#define LZZ_smtc_ParamPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_ParamPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <ParamPtr> ParamPtrVector;
}
namespace smtc
{
  typedef std::vector <ParamPtr>::iterator ParamPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <ParamPtr>::const_iterator ParamPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <ParamPtr>::reverse_iterator ParamPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <ParamPtr>::const_reverse_iterator ParamPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
