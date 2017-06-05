// smtc_TypeKind.h
//

#ifndef LZZ_smtc_TypeKind_h
#define LZZ_smtc_TypeKind_h
#define LZZ_INLINE inline
namespace smtc
{
  enum TypeKind
  {
    BOOL_TYPE,
    CHAR_TYPE,
    SIGNED_CHAR_TYPE,
    UNSIGNED_CHAR_TYPE,
    WIDE_CHAR_TYPE,
    SHORT_INT_TYPE,
    UNSIGNED_SHORT_INT,
    INT_TYPE,
    UNSIGNED_INT_TYPE,
    LONG_INT_TYPE,
    UNSIGNED_LONG_INT_TYPE,
    LONG_LONG_INT_TYPE,
    UNSIGNED_LONG_LONG_INT_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    LONG_DOUBLE_TYPE,
    VOID_TYPE,
    USER_TYPE,
    ELAB_TYPE,
    PTR_TYPE,
    MBR_PTR_TYPE,
    REF_TYPE,
    FUNC_TYPE,
    ARRAY_TYPE,
    NO_TYPE
  };
}
#undef LZZ_INLINE
#endif
