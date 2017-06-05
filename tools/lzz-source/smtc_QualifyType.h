// smtc_QualifyType.h
//

#ifndef LZZ_smtc_QualifyType_h
#define LZZ_smtc_QualifyType_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"

// util
#include "util_IdentSet.h"
#define LZZ_INLINE inline
namespace smtc
{
  bool qualifyType (CvType const & cv_type, util::IdentSet const & type_name_set, NamePtr const & qual_name, bool dpdt, CvType & res_cv_type);
}
#undef LZZ_INLINE
#endif
