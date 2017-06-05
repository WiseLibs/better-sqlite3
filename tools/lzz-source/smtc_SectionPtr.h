// smtc_SectionPtr.h
//

#ifndef LZZ_smtc_SectionPtr_h
#define LZZ_smtc_SectionPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Section;
}
namespace smtc
{
  typedef util::BPtr <Section> SectionPtr;
}
#undef LZZ_INLINE
#endif
