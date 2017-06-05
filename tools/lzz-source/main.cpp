// main.cpp
//

#include "main.h"
// semantic
#include "smtc_Lzz.h"
#include "msg_Output.h"
#include "msg_Recorder.h"

// config
#include "conf_Config.h"

#ifdef CGI_BUILD
#include <fstream>
#include "smtc_File.h"
#include "smtc_Output.h"
#endif

#define LZZ_INLINE inline
int main (int argc, char * * argv)
{
  int ret_code = 0;
  try
  {
    // console output is std::cout
    std::ostream & os = std::cout;

    // print messages to console
    msg::setMessageOut (os);

    // parse options
    util::StringDeque filenames;
    if (! conf::parseOptions (argc, argv, filenames) || msg::hasAnyFatalMessage ())
    {
      ret_code = 1;
    }
    else
    {
      smtc::compileFiles (filenames, os);
    }
  }
  catch (...)
  {
    ret_code = 1;
  }
  if (msg::hasAnyFatalMessage ())
  {
    ret_code = 1;
  }
  return ret_code;
}
#undef LZZ_INLINE
