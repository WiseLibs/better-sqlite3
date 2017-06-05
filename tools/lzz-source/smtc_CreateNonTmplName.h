// smtc_CreateNonTmplName.h
//

#ifndef LZZ_smtc_CreateNonTmplName_h
#define LZZ_smtc_CreateNonTmplName_h
#include "smtc_BaseNamePtr.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr createNonTmplName (BaseNamePtr const & base_name);
}
#undef LZZ_INLINE
#endif
