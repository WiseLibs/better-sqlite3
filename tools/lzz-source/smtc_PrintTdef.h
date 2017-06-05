// smtc_PrintTdef.h
//

#ifndef LZZ_smtc_PrintTdef_h
#define LZZ_smtc_PrintTdef_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_TdefPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printTdef (FilePtr const & file, TdefPtr const & tdef, NsPtr const & ns);
}
namespace smtc
{
  void printTdef (FilePtr const & file, TdefPtr const & tdef);
}
#undef LZZ_INLINE
#endif
