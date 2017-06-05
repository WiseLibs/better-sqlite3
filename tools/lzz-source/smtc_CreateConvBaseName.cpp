// smtc_CreateConvBaseName.cpp
//

#include "smtc_CreateConvBaseName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_CreateConvBaseName.inl"
#endif
// semantic
#include "smtc_ConvBaseName.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseNamePtr createConvBaseName (util::Loc const & loc, util::Ident const & macro, CvType const & cv_type)
  {
    return new ConvBaseName (loc, macro, cv_type);
  }
}
#undef LZZ_INLINE
