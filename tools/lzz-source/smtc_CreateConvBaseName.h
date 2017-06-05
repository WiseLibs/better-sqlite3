// smtc_CreateConvBaseName.h
//

#ifndef LZZ_smtc_CreateConvBaseName_h
#define LZZ_smtc_CreateConvBaseName_h
// semantic
#include "smtc_BaseNamePtr.h"
#include "smtc_CvType.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseNamePtr createConvBaseName (util::Loc const & loc, CvType const & cv_type);
}
namespace smtc
{
  BaseNamePtr createConvBaseName (util::Loc const & loc, util::Ident const & macro, CvType const & cv_type);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_CreateConvBaseName.inl"
#endif
#endif
