// smtc_UserType.cpp
//

#include "smtc_UserType.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_UserType.inl"
#endif
// semantic
#include "smtc_NameToString.h"
#include "smtc_AppendCv.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  UserType::UserType (NamePtr const & name)
    : m_name (name)
    {}
}
namespace smtc
{
  UserType::~ UserType ()
    {}
}
namespace smtc
{
  TypeKind UserType::getKind () const
    {
      return USER_TYPE;
    }
}
namespace smtc
{
  util::String UserType::toString (util::String const & dcl, bool c, bool v) const
    {
      using namespace util;
      String str = nameToString (m_name);
      appendCv (str, c, v);
      // enclose dcl if starts with global scope operator
      if (! (c || v) && dcl [0] == ':')
      {
        appendWithSpace (str, '(');
        str += dcl;
        str += ')';
      }
      else
      {
        appendWithSpace (str, dcl);
      }
      return str;
    }
}
#undef LZZ_INLINE
