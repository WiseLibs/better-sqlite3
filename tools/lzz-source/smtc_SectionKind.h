// smtc_SectionKind.h
//

#ifndef LZZ_smtc_SectionKind_h
#define LZZ_smtc_SectionKind_h
#define LZZ_INLINE inline
namespace smtc
{
  enum SectionKind
  {
    HEADER_SECTION,
    USER_SECTION,
    TOP_SECTION,
    DECLARATION_SECTION,
    BODY_SECTION,
    INLINE_HEADER_SECTION,
    INLINE_USER_SECTION,
    INLINE_TOP_SECTION,
    INLINE_BODY_SECTION,
    INLINE_TAIL_SECTION,
    TAIL_SECTION
  };
}
#undef LZZ_INLINE
#endif
