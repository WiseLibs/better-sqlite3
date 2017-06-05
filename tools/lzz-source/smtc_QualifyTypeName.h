// smtc_QualifyTypeName.h
//

#ifndef LZZ_smtc_QualifyTypeName_h
#define LZZ_smtc_QualifyTypeName_h
// semantic
#include "smtc_NamePtr.h"

// util
#include "util_IdentSet.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool qualifyTypeName (NamePtr const & name, util::IdentSet const & type_name_set, NamePtr const & qual_name, NamePtr & res_name);
}
#undef LZZ_INLINE
#endif
