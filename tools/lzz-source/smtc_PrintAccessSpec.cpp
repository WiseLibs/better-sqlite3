// smtc_PrintAccessSpec.cpp
//

#include "smtc_PrintAccessSpec.h"
// semantic
#include "smtc_AccessSpec.h"
#include "smtc_AccessToString.h"
#include "smtc_PrintCode.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  void printAccessSpec (FilePtr const & file, AccessSpecPtr const & access_spec)
  {
    String str = accessToString (access_spec->getAccess ());
    str += ':';
    printLine (file, DECLARATION_SECTION, access_spec->getLoc (), -1, str);
  }
}
#undef LZZ_INLINE
