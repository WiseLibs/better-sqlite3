// msg_Message.h
//

#ifndef LZZ_msg_Message_h
#define LZZ_msg_Message_h
// util
#include "util_Ident.h"
#include "util_String.h"

// message
#include "msg_Severity.h"
#define LZZ_INLINE inline
namespace msg
{
  class Message
  {
    Severity m_severity;
    util::String m_str;
    int m_arg_num;
  public:
    Message (Severity severity, char const * str);
    Message (char const * str);
    ~ Message ();
    void addArg (char const * arg);
    Message & operator << (char const * arg);
    Message & operator << (util::String const & arg);
    Message & operator << (util::Ident const & arg);
    Message & operator << (int arg);
    Severity getSeverity () const;
    util::String const & getString () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "msg_Message.inl"
#endif
#endif
