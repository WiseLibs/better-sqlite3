// msg_Output.cpp
//

#include "msg_Output.h"
// std lib
#include <cassert>

// message
#include "msg_Message.h"
#include "msg_Recorder.h"

// util
#include "util_LocToString.h"
#define LZZ_INLINE inline
namespace
{
  std::ostream * msg_os = 0;
}
namespace msg
{
  void setMessageOut (std::ostream & os)
  {
    msg_os = & os;
  }
}
namespace msg
{
  std::ostream & getMessageOut ()
  {
    // std::cout if not previously set
    return msg_os == 0 ? std::cout : * msg_os;
  }
}
namespace msg
{
  void print (util::Loc const & loc, Message const & msg)
  {
    util::String const & str = msg.getString ();
    assert (str.find ('%') == util::String::npos);
    getMessageOut () << util::locToString (loc) << str << std::endl;
    recordSeverity (msg.getSeverity ());
  }
}
namespace msg
{
  void print (Message const & msg)
  {
    util::String const & str = msg.getString ();
    assert (str.find ('%') == util::String::npos);
    getMessageOut () << str << std::endl;
    recordSeverity (msg.getSeverity ());
  }
}
#undef LZZ_INLINE
