// smtc_CreateQualName.h
//

#ifndef LZZ_smtc_CreateQualName_h
#define LZZ_smtc_CreateQualName_h
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr createQualName (NamePtr const & qual_name, NamePtr const & unql_name);
}
#undef LZZ_INLINE
#endif
