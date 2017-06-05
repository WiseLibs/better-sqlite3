// smtc_ArgListToString.cpp
//

#include "smtc_ArgListToString.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ArgListToString.inl"
#endif
// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  util::String argListToString (gram::BlockVector const & arg_list, int & num_lines)
  {
    String str;
    for (gram::BlockVectorConstIter beg = arg_list.begin (), end = arg_list.end (); beg != end; ++ beg)
    {
      gram::Block const & block = * beg;
      appendWithSpace (str, block.toString ());
      // do we need this?
      /*
      num_lines += block.getNumLines ();
      */
      if (beg + 1 != arg_list.end ())
      {
        str += ',';
      }
    }
    return str;
  }
}
#undef LZZ_INLINE
