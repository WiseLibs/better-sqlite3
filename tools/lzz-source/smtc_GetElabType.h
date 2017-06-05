// smtc_GetElabType.h
//

#ifndef LZZ_smtc_GetElabType_h
#define LZZ_smtc_GetElabType_h
// semantic
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#include "smtc_TypePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getElabType (ClassKey key, NamePtr const & name);
}
#undef LZZ_INLINE
#endif
