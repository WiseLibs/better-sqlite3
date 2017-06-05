// smtc_CreateQualName.cpp
//

#include "smtc_CreateQualName.h"
#include "smtc_QualName.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr createQualName (NamePtr const & qual_name, NamePtr const & unql_name)
  {
    return new QualName (qual_name, unql_name);
  }
}
#undef LZZ_INLINE
