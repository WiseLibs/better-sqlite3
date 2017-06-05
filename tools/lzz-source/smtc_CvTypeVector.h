// smtc_CvTypeVector.h
//

#ifndef LZZ_smtc_CvTypeVector_h
#define LZZ_smtc_CvTypeVector_h
// std lib
#include <vector>

// semantic
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <CvType> CvTypeVector;
}
namespace smtc
{
  typedef std::vector <CvType>::iterator CvTypeVectorIter;
}
namespace smtc
{
  typedef std::vector <CvType>::const_iterator CvTypeVectorConstIter;
}
namespace smtc
{
  typedef std::vector <CvType>::reverse_iterator CvTypeVectorRevIter;
}
namespace smtc
{
  typedef std::vector <CvType>::const_reverse_iterator CvTypeVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
