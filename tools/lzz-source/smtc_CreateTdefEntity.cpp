// smtc_CreateTdefEntity.cpp
//

#include "smtc_CreateTdefEntity.h"
// semantic
#include "smtc_TdefEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTdefEntity (TdefPtr const & tdef)
  {
    return new TdefEntity (tdef);
  }
}
#undef LZZ_INLINE
