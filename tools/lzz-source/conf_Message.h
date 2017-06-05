// conf_Message.h
//

#ifndef LZZ_conf_Message_h
#define LZZ_conf_Message_h
#define LZZ_INLINE inline
namespace conf
{
  namespace msg
  {
    void optionExpected (bool env = false);
  }
}
namespace conf
{
  namespace msg
  {
    void invalidOption (char const * opt, bool env = false);
  }
}
namespace conf
{
  namespace msg
  {
    void notBoolOption (char const * opt, bool env = false);
  }
}
namespace conf
{
  namespace msg
  {
    void optionValueExpected (char const * opt, bool env = false);
  }
}
namespace conf
{
  namespace msg
  {
    void disabledOption (char const * opt, bool env = false);
  }
}
namespace conf
{
  namespace msg
  {
    void filenameNotAccepted (char const * name);
  }
}
namespace conf
{
  namespace msg
  {
    void noFiles ();
  }
}
namespace conf
{
  namespace msg
  {
    void dllExportsNotSet ();
  }
}
namespace conf
{
  namespace msg
  {
    void typeHelpForUsage ();
  }
}
#undef LZZ_INLINE
#endif
