// gram_CreateFileStat.cpp
//

#include "gram_CreateFileStat.h"
// gram
#include "gram_FileStat.h"
#define LZZ_INLINE inline
namespace gram
{
  FileStatPtr createFileStat (util::Filename const & filename, bool insert)
  {
    return new FileStat (filename, insert);
  }
}
namespace gram
{
  FileStatPtr createFileStat (util::String const & str, util::Loc const & loc, bool insert)
  {
    return new FileStat (str, loc, insert);
  }
}
#undef LZZ_INLINE
