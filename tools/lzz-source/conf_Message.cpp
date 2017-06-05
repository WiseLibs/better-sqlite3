// conf_Message.cpp
//

#include "conf_Message.h"
// message
#include "msg_Message.h"
#include "msg_Output.h"
#define LZZ_INLINE inline
namespace conf
{
  namespace msg
  {
    using namespace ::msg;
  }
}
namespace conf
{
  namespace msg
  {
    void optionExpected (bool env)
  {
    static char const str [] = "Option expected after '-'.";
    static char const str_env [] = "Option expected after '-' in LZZ_OPTIONS.";
    print (Message (ERROR_MSG, env ? str_env : str));
  }
  }
}
namespace conf
{
  namespace msg
  {
    void invalidOption (char const * opt, bool env)
  {
    static char const str [] = "'%1' is not a recognized option.";
    static char const str_env [] = "'%1' is not a recognized option in LZZ_OPTIONS.";
    print (Message (ERROR_MSG, env ? str_env : str) << opt);
  }
  }
}
namespace conf
{
  namespace msg
  {
    void notBoolOption (char const * opt, bool env)
  {
    static char const str [] = "'%1' is not a boolean option.";
    static char const str_env [] = "'%1' is not a boolean option in LZZ_OPTIONS.";
    print (Message (ERROR_MSG, env ? str_env : str) << opt);
  }
  }
}
namespace conf
{
  namespace msg
  {
    void optionValueExpected (char const * opt, bool env)
  {
    static char const str [] = "Value expected for option '%1'.";
    static char const str_env [] = "Value expected for option '%1' in LZZ_OPTIONS.";
    print (Message (ERROR_MSG, env ? str_env : str) << opt);
  }
  }
}
namespace conf
{
  namespace msg
  {
    void disabledOption (char const * opt, bool env)
  {
    static char const str [] = "Option '%1' is disabled.";
    static char const str_env [] = "Option '%1' is disabled in LZZ_OPTIONS.";
    print (Message (ERROR_MSG, env ? str_env : str) << opt);
  }
  }
}
namespace conf
{
  namespace msg
  {
    void filenameNotAccepted (char const * name)
  {
    static char const str [] = "Filename '%1' not accepted.";
    print (Message (ERROR_MSG, str) << name);
  }
  }
}
namespace conf
{
  namespace msg
  {
    void noFiles ()
  {
    static char const str [] = "No files specified.";
    print (Message (ERROR_MSG, str));
  }
  }
}
namespace conf
{
  namespace msg
  {
    void dllExportsNotSet ()
  {
    static char const str [] = "if setting dll api macro (-da) then dll exports macro must be set too (-dx).";
    print (Message (ERROR_MSG, str));
  }
  }
}
namespace conf
{
  namespace msg
  {
    void typeHelpForUsage ()
  {
    static char const str [] = "Type 'lzz -h' for usage.";
    print (Message (INFO_MSG, str));
  }
  }
}
#undef LZZ_INLINE
