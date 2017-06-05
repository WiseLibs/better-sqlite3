// util_FilenameTable.cpp
//

#include "util_FilenameTable.h"
// util
#include "util_FileOp.h"
#include "util_FilenameImpl.h"
#include "util_FilenameImplPtrDataTable.h"
#include "util_GetRealPath.h"
#include "util_StringTable.h"
#define LZZ_INLINE inline
namespace
{
  using namespace util;
}
namespace
{
  struct FilenameTable
  {
    FilenameImplPtrDataTable data_table;
    bool getFilename (util::String const & name_str, Filename & filename);
    Filename storeFilename (util::String const & name_str);
  };
}
namespace
{
  FilenameTable & getFilenameTable ();
}
namespace
{
  bool FilenameTable::getFilename (util::String const & name_str, Filename & filename)
    {
      char const * name = storeString (file_op::dos2unix (name_str));
      FilenameImplPtrDataTableFindResult result = data_table.findData ((size_t) name);
      if (result.hasData ())
      {
        filename = Filename (result.getData ().pointer ());
        return true;
      }
      String realname_str;
      if (getRealPath (name_str, realname_str))
      {
        char const * realname = storeString (file_op::dos2unix (realname_str));
        FilenameImplPtr impl = new FilenameImpl (name, realname);
        data_table.addData (result, impl);
        filename = Filename (impl.pointer ());
        return true;
      }
      return false;
    }
}
namespace
{
  Filename FilenameTable::storeFilename (util::String const & name_str)
    {
      char const * name = storeString (file_op::dos2unix (name_str));
      FilenameImplPtrDataTableFindResult result = data_table.findData ((size_t) name);
      if (result.hasData ())
      {
        return Filename (result.getData ().pointer ());
      }
      char const * realname = name;
      FilenameImplPtr impl = new FilenameImpl (name, realname);
      data_table.addData (result, impl);
      return Filename (impl.pointer ());
    }
}
namespace
{
  FilenameTable & getFilenameTable ()
  {
    static FilenameTable table;
    return table;
  }
}
namespace util
{
  bool getFilename (util::String const & name, Filename & filename)
  {
    return getFilenameTable ().getFilename (name, filename);
  }
}
namespace util
{
  Filename storeFilename (util::String const & name)
  {
    return getFilenameTable ().storeFilename (name);
  }
}
#undef LZZ_INLINE
