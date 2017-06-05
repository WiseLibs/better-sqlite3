// smtc_ElabType.cpp
//

#include "smtc_ElabType.h"
// semantic
#include "smtc_AppendCv.h"
#include "smtc_ClassKeyToString.h"
#include "smtc_NameToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  ElabType::ElabType (ClassKey key, NamePtr const & name)
    : m_key (key), m_name (name)
    {}
}
namespace smtc
{
  ElabType::~ ElabType ()
    {}
}
namespace smtc
{
  TypeKind ElabType::getKind () const
    {
      return ELAB_TYPE;
    }
}
namespace smtc
{
  util::String ElabType::toString (util::String const & dcl, bool c, bool v) const
    {
      using namespace util;
      String str = classKeyToString (m_key);
      appendWithSpace (str, nameToString (m_name));
      appendCv (str, c, v);
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
