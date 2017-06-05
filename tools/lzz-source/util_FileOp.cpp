// util_FileOp.cpp
//

#include "util_FileOp.h"
#if defined WIN32
#define WINDOWS
#else
#define LINUX
#endif

#include <sys/stat.h>
#if defined WINDOWS
#include <io.h>
#elif defined LINUX
#include <unistd.h>
#endif

#ifndef F_OK
#if defined WINDOWS
#define F_OK 0
#endif
#endif

#ifndef S_ISREG
#define S_ISREG(mode) (((mode) & _S_IFMT) == _S_IFREG)
#endif

#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode) & _S_IFMT) == _S_IFDIR)
#endif

#include <iostream>
using namespace std;
#define LZZ_INLINE inline
namespace util
{
  namespace file_op
  {
    String remExt (String const & filename)
    {
      String result;
      int dot = filename.find_last_of ('.');
      int slash = filename.find_last_of ("/\\");
      if (dot != String::npos && (slash == String::npos || slash < dot))
      {
        result = filename.substr (0, dot);
      }
      else
      {
        result = filename;
      }      
      return result;
    }
  }
}
namespace util
{
  namespace file_op
  {
    String addExt (String const & filename, String const & ext)
    {
      String result = filename;
      result += '.';
      result += ext;
      return result;
    }
  }
}
namespace util
{
  namespace file_op
  {
    void getPathAndName (String const & filename, String & path, String & name)
    {
#if defined LINUX
      int len = filename.length ();
      while (len > 0 && filename [len - 1] == '/')
      {
        -- len;
      }
      int p = filename.rfind ('/', len);
      if (p == String::npos)
      {
        name = filename.substr (0, len);
        path = "./";
      }
      else
      {
        path = filename.substr (0, p + 1);
        name = filename.substr (p + 1, len - (p + 1));
      }
#elif defined WINDOWS
      int len = filename.length ();
      while (len > 0 && (filename [len - 1] == '\\' || filename [len - 1] == '/'))
      {
        -- len;
      }
      int p = filename.find_last_of ("/\\", len);
      if (p == String::npos)
      {
        name = filename.substr (0, len);
        path = ".\\";
      }
      else
      {
        path = filename.substr (0, p + 1);
        name = filename.substr (p + 1, len - (p + 1)); 
      }
#endif
    }
  }
}
namespace util
{
  namespace file_op
  {
    util::String getPath (String const & filename)
    {
      String path, name;
      getPathAndName (filename, path, name);
      return path;
    }
  }
}
namespace util
{
  namespace file_op
  {
    String join (String const & dirname, String const & filename)
    {
      String result = dirname;
      int len = result.length ();
      if (len > 0 && ! (result [len - 1] == '/' || result [len - 1] == '\\'))
      {
        result += '/';
      }
      result += filename;
      return result;
    }
  }
}
namespace util
{
  namespace file_op
  {
    bool exists (String const & filename)
    {
      bool result = false;
      if (access (filename.c_str (), F_OK) == 0)
      {
        result = true;
      }
      return result;
    }
  }
}
namespace util
{
  namespace file_op
  {
    String dos2unix (String const & filename)
    {
      String result = filename;
      int p;
      while ((p = result.find ('\\')) != String::npos)
      {
        result.replace (p, 1, "/");
      }
      return result;
    }
  }
}
namespace util
{
  namespace file_op
  {
    bool isAbsolute (String const & filename)
    {
      bool result = false;
#ifdef WINDOWS
      // true if starts with '\', '/' or drive letter
      result = filename.length () > 0 && (filename [0] == '\\' || filename [0] == '/') || filename.length () > 1 && filename [0] == ':';
#else
      // true if starts with '/'
      result = filename.length () > 0 && filename [0] == '/';
#endif
      return result;
    }
  }
}
namespace util
{
  namespace file_op
  {
    bool isDirectory (String const & filename)
    {
      struct stat fs;
      return stat (filename.c_str (), & fs) == 0 && S_ISDIR (fs.st_mode);
    }
  }
}
#undef LZZ_INLINE
