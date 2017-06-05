// msg_Message.cpp
//

#include "msg_Message.h"
#ifndef LZZ_ENABLE_INLINE
#include "msg_Message.inl"
#endif
// std lib
#include <cassert>

// util
#include "util_IntToString.h"
#define LZZ_INLINE inline
namespace msg
{
  Message::Message (Severity severity, char const * str)
    : m_severity (severity), m_str (str), m_arg_num (1)
    {}
}
namespace msg
{
  Message::Message (char const * str)
    : m_severity (ERROR_MSG), m_str (str), m_arg_num (1)
    {}
}
namespace msg
{
  Message::~ Message ()
    {}
}
namespace msg
{
  void Message::addArg (char const * arg)
    {
      util::String param ("%");
      param += util::intToString (m_arg_num ++);
      util::String::size_type p = m_str.find (param);
      assert (p != util::String::npos);
      m_str.replace (p, param.length (), arg);
    }
}
namespace msg
{
  Message & Message::operator << (char const * arg)
    {
      addArg (arg);
      return * this;
    }
}
namespace msg
{
  Message & Message::operator << (util::String const & arg)
    {
      addArg (arg.c_str ());
      return * this;
    }
}
namespace msg
{
  Message & Message::operator << (util::Ident const & arg)
    {
      addArg (arg.c_str ());
      return * this;
    }
}
namespace msg
{
  Message & Message::operator << (int arg)
    {
      util::String str_arg = util::intToString (arg);
      addArg (str_arg.c_str ());
      return * this;
    }
}
#undef LZZ_INLINE
