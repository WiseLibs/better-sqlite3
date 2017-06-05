// smtc_File.cpp
//

#include "smtc_File.h"
// std lib
#include <unistd.h>
#include <functional>
#include <algorithm>

// semantic
#include "smtc_Message.h"
#include "smtc_Section.h"

// util
#include "util_Exception.h"
#include "util_FileOp.h"
#include "util_GetTempFile.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  bool cmpfile (char const * str, int pcount, FILE * fp);
}
namespace
{
  struct FreezeSection
  {
    void operator () (SectionPtr const & section) const;
  public:
    explicit FreezeSection ();
    ~ FreezeSection ();
  };
}
namespace
{
  struct CompareSection : std::unary_function <SectionPtr, bool>
  {
    FILE * fp;
    bool operator () (SectionPtr const & section) const;
  public:
    explicit CompareSection (FILE * fp);
    ~ CompareSection ();
  };
}
namespace
{
  struct WriteSection
  {
    FILE * fp;
    void operator () (SectionPtr const & section) const;
  public:
    explicit WriteSection (FILE * fp);
    ~ WriteSection ();
  };
}
namespace
{
  struct IsSectionKind
  {
    SectionKind kind;
    bool operator () (SectionPtr const & section) const;
  public:
    explicit IsSectionKind (SectionKind kind);
    ~ IsSectionKind ();
  };
}
namespace
{
  bool cmpfile (char const * str, int pcount, FILE * fp)
  {
    bool match = true;
    for (; pcount > 0; -- pcount, ++ str)
    {
      int ch = fgetc (fp);
      if (ch == EOF || * str != ch)
      {
        match = false;
        break;
      }
    }
    return match;
  }
}
namespace
{
  void FreezeSection::operator () (SectionPtr const & section) const
  {
    section->freeze ();
  }
}
namespace
{
  LZZ_INLINE FreezeSection::FreezeSection ()
       {}
}
namespace
{
  FreezeSection::~ FreezeSection ()
       {}
}
namespace
{
  bool CompareSection::operator () (SectionPtr const & section) const
  {
    bool match = true;
    int size; 
    char const * str = section->toString (size);
    for (; size > 0; -- size, ++ str)
    {
      int ch = fgetc (fp);
      if (ch == EOF || * str != ch)
      {
        match = false;
        break;
      }
    }
    return match;
  }
}
namespace
{
  LZZ_INLINE CompareSection::CompareSection (FILE * fp)
    : fp (fp)
       {}
}
namespace
{
  CompareSection::~ CompareSection ()
       {}
}
namespace
{
  void WriteSection::operator () (SectionPtr const & section) const
  {
    int size;
    char const * str = section->toString (size);
    fwrite (str, sizeof (char), size, fp);
  }
}
namespace
{
  LZZ_INLINE WriteSection::WriteSection (FILE * fp)
    : fp (fp)
       {}
}
namespace
{
  WriteSection::~ WriteSection ()
       {}
}
namespace
{
  bool IsSectionKind::operator () (SectionPtr const & section) const
  {
    return section->getKind () == kind;
  }
}
namespace
{
  LZZ_INLINE IsSectionKind::IsSectionKind (SectionKind kind)
    : kind (kind)
       {}
}
namespace
{
  IsSectionKind::~ IsSectionKind ()
       {}
}
namespace smtc
{
  File::File (util::String const & fullname, util::String const & name, util::String const & ext, bool has_hash_lines, bool smart_write)
    : m_fullname (fullname), m_name (name), m_ext (ext), m_has_hash_lines (has_hash_lines), m_smart_write (smart_write), m_closed (false)
    {}
}
namespace smtc
{
  File::~ File ()
    {}
}
namespace smtc
{
  util::String const & File::getFullName () const
    {
      return m_fullname;
    }
}
namespace smtc
{
  util::String const & File::getName () const
    {
      return m_name;
    }
}
namespace smtc
{
  util::String const & File::getExt () const
    {
      return m_ext;
    }
}
namespace smtc
{
  bool File::isClosed () const
    {
      return m_closed;
    }
}
namespace smtc
{
  bool File::hasHashLines () const
    {
      return m_has_hash_lines;
    }
}
namespace smtc
{
  bool File::hasSection (SectionKind kind, SectionPtr & section)
    {
      bool result = false;
      SectionPtrVectorConstIter i = std::find_if (m_sections.begin (), m_sections.end (), IsSectionKind (kind));
      if (i != m_sections.end ())
      {
        section = (* i).unref ();
        result = true;
      }
      return result;
    }
}
namespace smtc
{
  bool File::hasSection (SectionKind kind)
    {
      SectionPtr section;
      return hasSection (kind, section);
    }
}
namespace smtc
{
  SectionPtr File::getSection (SectionKind kind)
    {
      SectionPtr section;
      if (! hasSection (kind, section))
      {
        section = SectionPtr (new Section (kind));
        m_sections.push_back (section);
        section = section.unref ();
      }
      return section;
    }
}
namespace smtc
{
  std::ostream & File::getStream (SectionKind kind)
    {
      return getSection (kind)->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::indent (SectionKind kind, int offset)
    {
      return getSection (kind)->indent (offset);
    }
}
namespace smtc
{
  std::ostream & File::indentExactly (SectionKind kind, int num)
    {
      return getSection (kind)->indentExactly (num);
    }
}
namespace smtc
{
  void File::incIndent (SectionKind kind)
    {
      getSection (kind)->incIndent ();
    }
}
namespace smtc
{
  void File::decIndent (SectionKind kind)
    {
      getSection (kind)->decIndent ();
    }
}
namespace smtc
{
  void File::close (FileKind kind)
    {
      if (m_closed)
      {
        return;
      }
      m_closed = true;
      // freeze all sections
      std::for_each (m_sections.begin (), m_sections.end (), FreezeSection ());
      // order the sections
      SectionPtrVector out_sections;
      addSection (HEADER_SECTION, out_sections);
      if (kind == SOURCE_FILE)
      {
        // inline sections
        addSection (INLINE_HEADER_SECTION, out_sections);
        addSection (INLINE_USER_SECTION, out_sections);
        addSection (INLINE_TOP_SECTION, out_sections);
        addSection (INLINE_BODY_SECTION, out_sections);
        addSection (INLINE_TAIL_SECTION, out_sections);
      }
      addSection (USER_SECTION, out_sections);
      addSection (TOP_SECTION, out_sections);
      addSection (DECLARATION_SECTION, out_sections);
      addSection (BODY_SECTION, out_sections);
      if (kind == HEADER_FILE)
      {
        // inline sections
        addSection (INLINE_HEADER_SECTION, out_sections);
        addSection (INLINE_USER_SECTION, out_sections);
        addSection (INLINE_TOP_SECTION, out_sections);
        addSection (INLINE_BODY_SECTION, out_sections);
        addSection (INLINE_TAIL_SECTION, out_sections);
      }
      addSection (TAIL_SECTION, out_sections);
      // compare with existing file if smart write on
      bool write_file = true;
      if (m_smart_write && util::file_op::exists (m_fullname))
      {
        if (FILE * fp = fopen (m_fullname.c_str (), "r"))
        {
          write_file = ! (std::find_if (out_sections.begin (), out_sections.end (), std::not1 (CompareSection (fp))) == out_sections.end ()
              && fgetc (fp) == EOF);
          fclose (fp);
        }
        else
        {
          msg::fileOpenError (m_fullname.c_str ());
          throw util::Exception ();
        }
      }
      if (write_file)
      {
        if (FILE * fp = fopen (m_fullname.c_str (), "w"))
        {
          std::for_each (out_sections.begin (), out_sections.end (), WriteSection (fp));
          fclose (fp);
        }
        else
        {
          msg::fileOpenError (m_fullname.c_str ());
          throw util::Exception ();
        }
      }
    }
}
namespace smtc
{
  SectionPtr File::getBodySection ()
    {
      return getSection (BODY_SECTION);
    }
}
namespace smtc
{
  SectionPtr File::getHeaderSection ()
    {
      return getSection (HEADER_SECTION);
    }
}
namespace smtc
{
  void File::incIndent ()
    {
      getBodySection ()->incIndent ();
    }
}
namespace smtc
{
  void File::decIndent ()
    {
      getBodySection ()->decIndent ();
    }
}
namespace smtc
{
  std::ostream & File::indent (int offset)
    {
      return getBodySection ()->indent (offset);
    }
}
namespace smtc
{
  std::ostream & File::indentExactly (int num)
    {
      return getBodySection ()->indentExactly (num);
    }
}
namespace smtc
{
  std::ostream & File::getStream ()
    {
      return getBodySection ()->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::header ()
    {
      return getHeaderSection ()->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::body ()
    {
      return getBodySection ()->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::top ()
    {
      return getSection (TOP_SECTION)->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::tail ()
    {
      return getSection (TAIL_SECTION)->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::inlineHeader ()
    {
      return getSection (INLINE_HEADER_SECTION)->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::inlineTop ()
    {
      return getSection (INLINE_TOP_SECTION)->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::inlineBody ()
    {
      return getSection (INLINE_BODY_SECTION)->getStream ();
    }
}
namespace smtc
{
  std::ostream & File::inlineTail ()
    {
      return getSection (INLINE_TAIL_SECTION)->getStream ();
    }
}
namespace smtc
{
  char const * File::freezeHeader (int & size)
    {
      return getHeaderSection ()->freeze (size);
    }
}
namespace smtc
{
  char const * File::freezeBody (int & size)
    {
      return getBodySection ()->freeze (size);
    }
}
namespace smtc
{
  void File::addSection (SectionKind kind, SectionPtrVector & out_sections)
    {
      SectionPtr section;
      if (hasSection (kind, section))
      {
        out_sections.push_back (section);
      }
    }
}
#undef LZZ_INLINE
