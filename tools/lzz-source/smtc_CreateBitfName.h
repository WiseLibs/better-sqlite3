// smtc_CreateBitfName.h
//

#ifndef LZZ_smtc_CreateBitfName_h
#define LZZ_smtc_CreateBitfName_h
// semantic
#include "smtc_NamePtr.h"

// gram
#include "gram_Block.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr createBitfName (util::Loc const & loc, util::Ident const & ident, gram::Block const & size);
}
#undef LZZ_INLINE
#endif
