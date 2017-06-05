// smtc_PrintEnum.cpp
//

#include "smtc_PrintEnum.h"
// semantic
#include "smtc_Enum.h"
#include "smtc_Enumtor.h"
#include "smtc_GetNameLoc.h"
#include "smtc_NameToString.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  void printEnumtor (FilePtr const & file, EnumtorPtr const & enumtor, bool comma);
}
namespace
{
  void printEnumtor (FilePtr const & file, EnumtorPtr const & enumtor, bool comma)
  {
    using namespace util;
    NamePtr const & name = enumtor->getName ();
    String str = nameToString (name);
    if (enumtor->hasInit ())
    {
      appendWithSpace (str, '=');
      appendWithSpace (str, enumtor->getInit ().toString ());
    }
    if (comma)
    {
      str += ',';
    }
    printLine (file, DECLARATION_SECTION, getNameLoc (name), str);
  }
}
namespace smtc
{
  void printEnum (FilePtr const & file, EnumPtr const & en, NsPtr const & ns)
  {
    int ns_depth = printNsOpen (file, DECLARATION_SECTION, ns);
    printEnum (file, en);
    printNsClose (file, DECLARATION_SECTION, ns_depth);
  }
}
namespace smtc
{
  void printEnum (FilePtr const & file, EnumPtr const & en)
  {
    using namespace util;
    String str = "enum";
    NamePtr const & name = en->getName ();
    if (name.isSet ())
    {
      appendWithSpace (str, nameToString (name));
    }
    printLine (file, DECLARATION_SECTION, en->getLoc (), str);
    printOpenBrace (file, DECLARATION_SECTION);
    EnumtorPtrVector const & enumtor_set = en->getEnumtorSet ();
    for (EnumtorPtrVectorConstIter beg = enumtor_set.begin (), end = enumtor_set.end (); beg != end; ++ beg)
    {
      printEnumtor (file, * beg, beg + 1 != end);
    }
    // close brace with semi
    printCloseBrace (file, DECLARATION_SECTION, true);
  }
}
#undef LZZ_INLINE
