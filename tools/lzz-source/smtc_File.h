// smtc_File.h
//

#ifndef LZZ_smtc_File_h
#define LZZ_smtc_File_h
// std lib
#include <strstream>
#include <cstdio>

// semantic
#include "smtc_SectionKind.h"
#include "smtc_SectionPtrVector.h"
#include "smtc_FileKind.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class File
  {
    util::String m_fullname;
    util::String m_name;
    util::String m_ext;
    bool m_has_hash_lines;
    bool m_smart_write;
    SectionPtrVector m_sections;
    bool m_closed;
  public:
    File (util::String const & fullname, util::String const & name, util::String const & ext, bool has_hash_lines, bool smart_write);
    ~ File ();
    util::String const & getFullName () const;
    util::String const & getName () const;
    util::String const & getExt () const;
    bool isClosed () const;
    bool hasHashLines () const;
    bool hasSection (SectionKind kind, SectionPtr & section);
    bool hasSection (SectionKind kind);
    SectionPtr getSection (SectionKind kind);
    std::ostream & getStream (SectionKind kind);
    std::ostream & indent (SectionKind kind, int offset = 0);
    std::ostream & indentExactly (SectionKind kind, int num);
    void incIndent (SectionKind kind);
    void decIndent (SectionKind kind);
    void close (FileKind kind);
    SectionPtr getBodySection ();
    SectionPtr getHeaderSection ();
    void incIndent ();
    void decIndent ();
    std::ostream & indent (int offset = 0);
    std::ostream & indentExactly (int num);
    std::ostream & getStream ();
    std::ostream & header ();
    std::ostream & body ();
    std::ostream & top ();
    std::ostream & tail ();
    std::ostream & inlineHeader ();
    std::ostream & inlineTop ();
    std::ostream & inlineBody ();
    std::ostream & inlineTail ();
    char const * freezeHeader (int & size);
    char const * freezeBody (int & size);
  private:
    void addSection (SectionKind kind, SectionPtrVector & out_sections);
  };
}
#undef LZZ_INLINE
#endif
