// smtc_PrintHandler.cpp
//

#include "smtc_PrintHandler.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintHandler.inl"
#endif
// semantic
#include "smtc_Handler.h"
#include "smtc_Param.h"
#include "smtc_PrintCode.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  void printHandler (FilePtr const & file, SectionKind skind, HandlerPtr const & handler)
  {
    String str = "catch";
    appendWithSpace (str, '(');
    ParamPtr const & catch_param = handler->getCatchParam ();
    if (catch_param.isSet ())
    {
      str += catch_param->toString (false);
    }
    else
    {
      str += "...";
    }
    str += ')';
    printLine (file, skind, handler->getLoc (), str);
    printEnclosedBlock (file, skind, handler->getBody ());
  }
}
namespace smtc
{
  PrintHandler::~ PrintHandler ()
              {}
}
#undef LZZ_INLINE
