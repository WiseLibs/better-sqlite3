// gram_FileStat.cpp
//

#include "gram_FileStat.h"
#define LZZ_INLINE inline
namespace gram
{
  IfStat::IfStat (util::Loc const & loc, int rs, int ss, bool guard)
    : loc (loc), rs (rs), ss (ss), guard (guard)
    {}
}
namespace gram
{
  IfStat::~ IfStat ()
    {}
}
namespace gram
{
  FileStat::FileStat (util::Filename const & filename, bool insert)
    : lexer (filename), realname (filename.getRealName ()), insert (insert), status (FILE_START)
    {
      // OK to use null location (only used if missing #endif, so in that case we'll always have pushed a location)
      is_stack.push_back (IfStat (util::Loc (), ON_RS, NONE_SS, false));
    }
}
namespace gram
{
  FileStat::FileStat (util::String const & str, util::Loc const & loc, bool insert)
    : lexer (str, loc), realname (loc.getFilename ().getRealName ()), insert (insert), status (FILE_START)
    {
      // OK to use null location (only used if missing #endif, so in that case we'll always have pushed a location)
      is_stack.push_back (IfStat (util::Loc (), ON_RS, NONE_SS, false));
    }
}
namespace gram
{
  FileStat::~ FileStat ()
    {}
}
#undef LZZ_INLINE
