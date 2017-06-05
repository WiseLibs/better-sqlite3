// gram_MacroKind.h
//

#ifndef LZZ_gram_MacroKind_h
#define LZZ_gram_MacroKind_h
// gram
#define LZZ_INLINE inline
namespace gram
{
  enum MacroKind
  {
    OBJ_MACRO,
    FUNC_MACRO,
    FILE_MACRO,
    LINE_MACRO
  };
}
#undef LZZ_INLINE
#endif
