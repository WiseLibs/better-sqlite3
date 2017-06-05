// msg_Recorder.h
//

#ifndef LZZ_msg_Recorder_h
#define LZZ_msg_Recorder_h
// message
#include "msg_Severity.h"
#define LZZ_INLINE inline
namespace msg
{
  void recordSeverity (Severity s);
}
namespace msg
{
  void resetRecorder ();
}
namespace msg
{
  bool hasFatalMessage ();
}
namespace msg
{
  bool hasWarningMessage ();
}
namespace msg
{
  bool hasInfoMessage ();
}
namespace msg
{
  bool hasAnyFatalMessage ();
}
namespace msg
{
  bool hasAnyWarningMessage ();
}
namespace msg
{
  bool hasAnyInfoMessage ();
}
namespace msg
{
  bool hasAnyMessage ();
}
#undef LZZ_INLINE
#endif
