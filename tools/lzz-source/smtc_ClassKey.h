// smtc_ClassKey.h
//

#ifndef LZZ_smtc_ClassKey_h
#define LZZ_smtc_ClassKey_h
#define LZZ_INLINE inline
namespace smtc
{
  enum ClassKey
  {
    CLASS_KEY,
    STRUCT_KEY,
    UNION_KEY,
    ENUM_KEY,
    TYPENAME_KEY
  };
}
#undef LZZ_INLINE
#endif
