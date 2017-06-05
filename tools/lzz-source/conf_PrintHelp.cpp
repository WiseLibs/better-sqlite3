// conf_PrintHelp.cpp
//

#include "conf_PrintHelp.h"
// std lib
#include <iostream>

// config
#include "conf_Config.h"
#include "conf_LzzVersion.h"
#include "conf_Option.h"
#define LZZ_INLINE inline
namespace
{
  char const (version_text) [] =
  {
    "Lzz: A C++ Component Generator, Version " LZZ_VERSION
#ifdef DEBUG_BUILD
    " DEBUG"
#endif
    "\n"
  };
}
namespace
{
  char const (usage_text) [] =
  {
    "Usage: lzz [options] filenames ...\n"
    "Options:\n"
    " -i       Output inline definitions to inline file.\n"
    " -t       Output template definitions to template file.\n"
    " -n       Output inline template definitions to template inline file.\n"
    " -hx EXT  Set header filename extension.\n"
    " -sx EXT  Set source filename extension.\n"
    " -ix EXT  Set inline filename extension.\n"
    " -tx EXT  Set template filename extension.\n"
    " -nx EXT  Set template inline filename extension.\n"
    " -hl      Ouput #lines in header file.\n"
    " -sl      Ouput #lines in source file.\n"
    " -il      Ouput #lines in inline file.\n"
    " -tl      Ouput #lines in template file.\n"
    " -nl      Ouput #lines in template inline file.\n"
    " -hd      Write header file only if different than previous.\n"
    " -sd      Write source file only if different than previous.\n"
    " -id      Write inline file only if different than previous.\n"
    " -td      Write template file only if different than previous.\n"
    " -nd      Write template inline file only if different than previous.\n"
    " -c       Create source file if header file is created.\n"
    " -e       Preprocess all code.\n"
    " -o DIR   Set output directory for files.\n"
    " -x       Use absolute filenames in #lines.\n"
    " -d       Delete old files no longer created.\n"
    " -I DIR   Search directory for #include and #insert files.\n"
    " -D MACRO Define function or object macro (replacement text follows '=').\n"
    " -da MACRO Set the macro that project defines to __declspec(dllimport) or __declspec(dllexport).\n"
    " -dx MACRO Set the macro that is non-zero when project is compiled to export DLL symbols.\n"
    " -a FNAME Automatically #include file at start of file.\n"
    " -k NAME  Set the package name (will embed in include guard).\n"
    " -p       Preprocess to stdout.\n"
    " -P       Preprocess to stdout, all code in file.\n"
    " -E       Preprocess to stdout, all code in file and #include files.\n"
    " -r CMDS  Set the syntax error recover commands.\n"

#ifdef DEBUG_BUILD
    " -tr      Print parse trace.\n"
#endif

    " -v       Print the values of the above options.\n"
    " -hr      Print the help text for the -r option.\n"
    " -T       Print token names usable in the -r option.\n"
    " -ver     Print the version number.\n"
    " -h\n"
    " -help    Print this help text.\n"
    "Options can also be specified in the environment variable LZZ_OPTIONS.\n"
    "To turn off a boolean option precede the option with '-no'.\n"
    "For further help, see http://www.lazycplusplus.com.\n"
    "Copyright (C) 2001-2011, Mike Spencer (mike@lazycplusplus.com)\n"
  };
}
namespace conf
{
  void printVersion (std::ostream & os)
  {
    os << version_text;
    os.flush ();
  }
}
namespace conf
{
  void printHelp (std::ostream & os)
  {
    os << version_text;
    os << usage_text;
    os.flush ();
  }
}
#undef LZZ_INLINE
