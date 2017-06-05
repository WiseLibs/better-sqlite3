// smtc_PrintNsNavClass.cpp
//

#include "smtc_PrintNsNavClass.h"
// semantic
#include "smtc_CompleteNavClass.h"
#include "smtc_PrintNsClassDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsNavClass (Output & out, NavClassPtr const & nav_class, NsPtr const & ns)
  {
    completeNavClass (nav_class);
    printNsClassDefn (out, nav_class, ns);
  }
}
#undef LZZ_INLINE
