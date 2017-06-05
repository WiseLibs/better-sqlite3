// msg_Recorder.cpp
//

#include "msg_Recorder.h"
// std lib
#include <cassert>
#define LZZ_INLINE inline
namespace
{
  using namespace msg;
}
namespace
{
  class Recorder
  {
    bool has_fatal;
    bool has_any_fatal;
    bool has_warning;
    bool has_any_warning;
    bool has_info;
    bool has_any_info;
  public:
    Recorder ();
    void reset ();
    void record (Severity s);
    bool hasFatalMessage () const;
    bool hasWarningMessage () const;
    bool hasInfoMessage () const;
    bool hasAnyFatalMessage () const;
    bool hasAnyWarningMessage () const;
    bool hasAnyInfoMessage () const;
  };
}
namespace
{
  Recorder & getRecorder ();
}
namespace
{
  Recorder::Recorder ()
    : has_fatal (false), has_warning (false), has_info (false), has_any_fatal (false), has_any_warning (false), has_any_info (false)
    {}
}
namespace
{
  void Recorder::reset ()
    {
      has_fatal = false;
      has_warning = false;
      has_info = false;
    }
}
namespace
{
  void Recorder::record (Severity s)
    {
      if (s == ERROR_MSG)
      {
        has_fatal = true;
        has_any_fatal = true;
      }
      else if (s == WARNING_MSG)
      {
        has_warning = true;
        has_any_warning = true;
      }
      else if (s == INFO_MSG)
      {
        has_info = true;
        has_any_info = true;
      }
      else
      {
        assert (false);
      }
    }
}
namespace
{
  LZZ_INLINE bool Recorder::hasFatalMessage () const
    {
      return has_fatal;
    }
}
namespace
{
  LZZ_INLINE bool Recorder::hasWarningMessage () const
    {
      return has_warning;
    }
}
namespace
{
  LZZ_INLINE bool Recorder::hasInfoMessage () const
    {
      return has_info;
    }
}
namespace
{
  LZZ_INLINE bool Recorder::hasAnyFatalMessage () const
    {
      return has_any_fatal;
    }
}
namespace
{
  LZZ_INLINE bool Recorder::hasAnyWarningMessage () const
    {
      return has_any_warning;
    }
}
namespace
{
  LZZ_INLINE bool Recorder::hasAnyInfoMessage () const
    {
      return has_any_info;
    }
}
namespace
{
  Recorder & getRecorder ()
  {
    static Recorder recorder;
    return recorder;
  }
}
namespace msg
{
  void recordSeverity (Severity s)
  {
    getRecorder ().record (s);
  }
}
namespace msg
{
  void resetRecorder ()
  {
    getRecorder ().reset ();
  }
}
namespace msg
{
  bool hasFatalMessage ()
  {
    return getRecorder ().hasFatalMessage ();
  }
}
namespace msg
{
  bool hasWarningMessage ()
  {
    return getRecorder ().hasWarningMessage ();
  }
}
namespace msg
{
  bool hasInfoMessage ()
  {
    return getRecorder ().hasInfoMessage ();
  }
}
namespace msg
{
  bool hasAnyFatalMessage ()
  {
    return getRecorder ().hasAnyFatalMessage ();
  }
}
namespace msg
{
  bool hasAnyWarningMessage ()
  {
    return getRecorder ().hasAnyWarningMessage ();
  }
}
namespace msg
{
  bool hasAnyInfoMessage ()
  {
    return getRecorder ().hasAnyInfoMessage ();
  }
}
namespace msg
{
  bool hasAnyMessage ()
  {
    return hasAnyFatalMessage () || hasAnyWarningMessage () || hasAnyInfoMessage ();
  }
}
#undef LZZ_INLINE
