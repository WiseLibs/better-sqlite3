// smtc_PrintNsClose.cpp
//

#include "smtc_PrintNsClose.h"
// semantic
#include "smtc_PrintCode.h"
#include "smtc_File.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsClose (FilePtr const & file, SectionKind skind, int depth)
  {
    for (int i = 0; i < depth; ++ i)
    {
      printCloseBrace (file, skind);
    }
  }
}
#undef LZZ_INLINE
