// smtc_ClassDeclToString.cpp
//

#include "smtc_ClassDeclToString.h"
// semantic
#include "smtc_ClassDecl.h"
#include "smtc_ClassKeyToString.h"
#include "smtc_NameToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  util::String classDeclToString (ClassDeclPtr const & class_decl)
  {
    String str = classKeyToString (class_decl->getKey ());
    appendWithSpace (str, nameToString (class_decl->getName ()));
    return str;
  }
}
#undef LZZ_INLINE
