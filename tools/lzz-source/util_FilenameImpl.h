// util_FilenameImpl.h
//

#ifndef LZZ_util_FilenameImpl_h
#define LZZ_util_FilenameImpl_h
#define LZZ_INLINE inline
namespace util
{
  struct FilenameImpl
  {
    char const * name;
    char const * realname;
    FilenameImpl (char const * name, char const * realname);
  };
}
#undef LZZ_INLINE
#endif
