// smtc_PrintNsTdef.cpp
//

#include "smtc_PrintNsTdef.h"
// semantic
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Output.h"
#include "smtc_PrintTdef.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsTdef (Output & out, TdefPtr const & tdef, NsPtr const & ns)
  {
    FilePtr file = isNsEnclUnmd (ns) ? out.getSrcFile () : out.getHdrFile ();
    printTdef (file, tdef, ns);
  }
}
#undef LZZ_INLINE
