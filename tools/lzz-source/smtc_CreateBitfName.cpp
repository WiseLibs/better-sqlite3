// smtc_CreateBitfName.cpp
//

#include "smtc_CreateBitfName.h"
// semantic
#include "smtc_BitfName.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr createBitfName (util::Loc const & loc, util::Ident const & ident, gram::Block const & size)
  {
    size.trim ();
    return new BitfName (loc, ident, size.toString ());
  }
}
#undef LZZ_INLINE
