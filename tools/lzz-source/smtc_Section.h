// smtc_Section.h
//

#ifndef LZZ_smtc_Section_h
#define LZZ_smtc_Section_h
// std lib
#include <strstream>
#include <cstring>
#include <cassert>

// semantic
#include "smtc_SectionKind.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Section
  {
    SectionKind m_kind;
    std::ostrstream m_os;
    int m_indent;
  public:
    Section (SectionKind kind);
    ~ Section ();
    SectionKind getKind () const;
    std::ostream & getStream ();
    std::ostream & indent (int offset = 0);
    std::ostream & indentExactly (int num);
    void incIndent ();
    void decIndent ();
    void freeze ();
    char const * freeze (int & size);
    char const * toString (int & size);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Section.inl"
#endif
#endif
