// smtc_PrintNsEnum.cpp
//

#include "smtc_PrintNsEnum.h"
// semantic
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintEnum.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsEnum (Output & out, EnumPtr const & en, NsPtr const & ns)
  {
    FilePtr const & file = isNsEnclUnmd (ns) ? out.getSrcFile () : out.getHdrFile ();
    printEnum (file, en, ns);
  }
}
#undef LZZ_INLINE
