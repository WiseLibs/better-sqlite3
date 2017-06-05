// util_FileOp.h
//

#ifndef LZZ_util_FileOp_h
#define LZZ_util_FileOp_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  namespace file_op
  {
    String remExt (String const & filename);
  }
}
namespace util
{
  namespace file_op
  {
    String addExt (String const & filename, String const & ext);
  }
}
namespace util
{
  namespace file_op
  {
    void getPathAndName (String const & filename, String & path, String & name);
  }
}
namespace util
{
  namespace file_op
  {
    util::String getPath (String const & filename);
  }
}
namespace util
{
  namespace file_op
  {
    String join (String const & dirname, String const & filename);
  }
}
namespace util
{
  namespace file_op
  {
    bool exists (String const & filename);
  }
}
namespace util
{
  namespace file_op
  {
    String dos2unix (String const & filename);
  }
}
namespace util
{
  namespace file_op
  {
    bool isAbsolute (String const & filename);
  }
}
namespace util
{
  namespace file_op
  {
    bool isDirectory (String const & filename);
  }
}
#undef LZZ_INLINE
#endif
