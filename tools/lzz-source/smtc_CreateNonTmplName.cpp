// smtc_CreateNonTmplName.cpp
//

#include "smtc_CreateNonTmplName.h"
#include "smtc_NonTmplName.h"
#define LZZ_INLINE inline
namespace smtc
{
  NamePtr createNonTmplName (BaseNamePtr const & base_name)
  {
    return new NonTmplName (base_name);
  }
}
#undef LZZ_INLINE
