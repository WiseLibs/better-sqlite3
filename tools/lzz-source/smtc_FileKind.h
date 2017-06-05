// smtc_FileKind.h
//

#ifndef LZZ_smtc_FileKind_h
#define LZZ_smtc_FileKind_h
#define LZZ_INLINE inline
namespace smtc
{
  enum FileKind
  {
    HEADER_FILE,
    SOURCE_FILE,
    INLINE_FILE,
    TEMPLATE_FILE,
    TEMPLATE_INLINE_FILE
  };
}
#undef LZZ_INLINE
#endif
