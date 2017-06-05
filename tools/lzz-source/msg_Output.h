// msg_Output.h
//

#ifndef LZZ_msg_Output_h
#define LZZ_msg_Output_h
#include <iostream>
#define LZZ_INLINE inline
namespace util
{
  class Loc;
}
namespace msg
{
  class Message;
}
namespace msg
{
  void setMessageOut (std::ostream & os);
}
namespace msg
{
  std::ostream & getMessageOut ();
}
namespace msg
{
  void print (util::Loc const & loc, Message const & msg);
}
namespace msg
{
  void print (Message const & msg);
}
#undef LZZ_INLINE
#endif
