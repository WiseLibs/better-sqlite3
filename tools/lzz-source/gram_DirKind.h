// gram_DirKind.h
//

#ifndef LZZ_gram_DirKind_h
#define LZZ_gram_DirKind_h
#define LZZ_INLINE inline
namespace gram
{
  enum DirKind
  {
    DEFINE_DIR,
    INCLUDE_DIR,
    IF_DIR,
    IFDEF_DIR,
    IFNDEF_DIR,
    ELIF_DIR,
    ELSE_DIR,
    ENDIF_DIR,
    UNDEF_DIR,
    LINE_DIR,
    ERROR_DIR,
    PRAGMA_DIR,
    WARNING_DIR,
    INSERT_DIR,
    HDR_DIR,
    SRC_DIR,
    INL_DIR,
    TPL_DIR,
    TNL_DIR
  };
}
#undef LZZ_INLINE
#endif
