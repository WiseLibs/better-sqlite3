// smtc_CreateTdefEntity.h
//

#ifndef LZZ_smtc_CreateTdefEntity_h
#define LZZ_smtc_CreateTdefEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_TdefPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTdefEntity (TdefPtr const & tdef);
}
#undef LZZ_INLINE
#endif
