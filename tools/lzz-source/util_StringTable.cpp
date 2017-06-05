// util_StringTable.cpp
//

#include "util_StringTable.h"
// util
#include "util_IdentTable.h"
#define LZZ_INLINE inline
namespace
{
  using namespace util;
}
namespace
{
  struct StringTable
  {
    IdentTable table;
    char const * storeString (char const * name);
  };
}
namespace
{
  StringTable & getStringTable ();
}
namespace
{
  char const * StringTable::storeString (char const * name)
    {
      return table.getIdent (name).c_str ();
    }
}
namespace
{
  StringTable & getStringTable ()
  {
    static StringTable table;
    return table;
  }
}
namespace util
{
  char const * storeString (util::String const & name)
  {
    return getStringTable ().storeString (name.c_str ());
  }
}
namespace util
{
  char const * storeString (char const * name)
  {
    return getStringTable ().storeString (name);
  }
}
#undef LZZ_INLINE
