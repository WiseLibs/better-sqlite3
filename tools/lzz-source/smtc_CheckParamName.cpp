// smtc_CheckParamName.cpp
//

#include "smtc_CheckParamName.h"
// semantic
#include "smtc_GetNameLoc.h"
#include "smtc_IsNameQual.h"
#include "smtc_Message.h"
#define LZZ_INLINE inline
namespace smtc
{
  void checkParamName (NamePtr const & name)
  {
    // name cannot be qualified
    if (isNameQual (name))
    {
      msg::qualParamName (getNameLoc (name));
    }
  }
}
#undef LZZ_INLINE
