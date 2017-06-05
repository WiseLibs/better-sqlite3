// gram_FileStat.h
//

#ifndef LZZ_gram_FileStat_h
#define LZZ_gram_FileStat_h
#include "gram_Lexer.h"
#include "util_Filename.h"
#include "util_Ident.h"
#include <vector>
#define LZZ_INLINE inline
namespace gram
{
  struct IfStat
  {
    util::Loc loc;
    int rs;
    int ss;
    bool guard;
    IfStat (util::Loc const & loc, int rs, int ss, bool guard);
    ~ IfStat ();
  };
}
namespace gram
{
  struct FileStat
  {
    char const * realname;
    Lexer lexer;
    std::vector <IfStat> is_stack;
    util::Ident guard_macro;
    int status;
    bool insert;
    FileStat (util::Filename const & filename, bool insert);
    FileStat (util::String const & str, util::Loc const & loc, bool insert);
    ~ FileStat ();
  };
}
namespace gram
{
  enum
  {
    FILE_START,
    FILE_BODY,
    FILE_ENDX
  };
}
namespace gram
{
  enum
  {
    ON_RS = 1 << 0,
    OFF_RS = 1 << 1,
    WAIT_RS = 1 << 2,
    NONE_SS = 1 << 3,
    IF_SS = 1 << 4,
    ELSE_SS = 1 << 5
  };
}
#undef LZZ_INLINE
#endif
