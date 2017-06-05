// smtc_SectionPtrVector.h
//

#ifndef LZZ_smtc_SectionPtrVector_h
#define LZZ_smtc_SectionPtrVector_h
// std lib
#include <vector>

// semantic
#include "smtc_SectionPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  typedef std::vector <SectionPtr> SectionPtrVector;
}
namespace smtc
{
  typedef std::vector <SectionPtr>::iterator SectionPtrVectorIter;
}
namespace smtc
{
  typedef std::vector <SectionPtr>::const_iterator SectionPtrVectorConstIter;
}
namespace smtc
{
  typedef std::vector <SectionPtr>::reverse_iterator SectionPtrVectorRevIter;
}
namespace smtc
{
  typedef std::vector <SectionPtr>::const_reverse_iterator SectionPtrVectorConstRevIter;
}
#undef LZZ_INLINE
#endif
