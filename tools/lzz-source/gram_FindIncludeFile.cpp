// gram_FindIncludeFile.cpp
//

#include "gram_FindIncludeFile.h"
// std lib
#include <algorithm>

// config
#include "conf_Config.h"

// util
#include "util_FileOp.h"
#define LZZ_INLINE inline
namespace
{
  using namespace util::file_op;
}
namespace
{
  bool findInDir (util::String const & dir, util::String const & name, util::String & fullname);
}
namespace
{
  struct FindInDir
  {
    util::String const & name;
    util::String & fullname;
    bool operator () (util::String const & dir) const;
  public:
    explicit FindInDir (util::String const & name, util::String & fullname);
    ~ FindInDir ();
  };
}
namespace gram
{
  using namespace util::file_op;
}
namespace
{
  bool findInDir (util::String const & dir, util::String const & name, util::String & fullname)
  {
    bool result = false;
    util::String file = join (dir, name);
    if (exists (file) && ! isDirectory (file))
    {
      result = true;
      fullname = file;
    }
    return result;
  }
}
namespace
{
  LZZ_INLINE bool FindInDir::operator () (util::String const & dir) const
  {
    return findInDir (dir, name, fullname);
  }
}
namespace
{
  LZZ_INLINE FindInDir::FindInDir (util::String const & name, util::String & fullname)
    : name (name), fullname (fullname)
              {}
}
namespace
{
  FindInDir::~ FindInDir ()
              {}
}
namespace gram
{
  bool findIncludeFile (util::String const & inclname, util::String const & name, bool sys, util::String & fullname)
  {
    // if absolute then no need to search path
    bool result = false;
    if (isAbsolute (name))
    {
      if (exists (name))
      {
        result = true;
        fullname = name;
      }
    }
    // otherwise search in curent dir if not sys 
    else if (! sys && findInDir (getPath (inclname), name, fullname))
    {
      result = true;
    }
    else
    {
      // search in path list
      util::StringVector const & path_set = conf::getOptionValue (conf::opt_incl_path_set);
      result = std::find_if (path_set.begin (), path_set.end (), FindInDir (name, fullname)) != path_set.end ();
    }
    return result;
  }
}
#undef LZZ_INLINE
