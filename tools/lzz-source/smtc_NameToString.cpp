// smtc_NameToString.cpp
//

#include "smtc_NameToString.h"
// semantic
#include "smtc_BaseNameToString.h"
#include "smtc_BitfName.h"
#include "smtc_NameVisitor.h"
#include "smtc_NonTmplName.h"
#include "smtc_QualName.h"
#include "smtc_TmplName.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct NameToString : NameVisitor
  {
    util::String & str;
    void visit (QualName const & name) const;
    void visit (TmplName const & name) const;
    void visit (NonTmplName const & name) const;
    void visit (BitfName const & name) const;
  public:
    explicit NameToString (util::String & str);
    ~ NameToString ();
  };
}
namespace
{
  void NameToString::visit (QualName const & name) const
    {
      NamePtr const & qual_name = name.getQualName ();
      if (qual_name.isSet ())
      {
        str = nameToString (qual_name);
      }
      str += "::";
      str += nameToString (name.getUnqlName ());
    }
}
namespace
{
  void NameToString::visit (TmplName const & name) const
    {
      if (name.hasTemplateKeyword ())
      {
        str = "template";
      }
      util::appendWithSpace (str, baseNameToString (name.getBaseName ()));
      util::appendWithSpace (str, '<');
      util::String const & args = name.getArgs ();
      // watch out for diagraph '<:'  
      if (! args.empty () && args [0] == ':')
      {
        str += ' ';
      }
      str += args;
      // watch out for nested template args
      if (str [str.length () - 1] == '>')
      {
        str += ' ';
      }
      str += '>';
    }
}
namespace
{
  void NameToString::visit (NonTmplName const & name) const
    {
      str = baseNameToString (name.getBaseName ());
    }
}
namespace
{
  void NameToString::visit (BitfName const & name) const
    {
      if (name.hasIdent ())
      {
        str = name.getIdent ().c_str ();
      }
      util::appendWithSpace (str, ':');
      util::appendWithSpace (str, name.getSize ());
    }
}
namespace
{
  LZZ_INLINE NameToString::NameToString (util::String & str)
    : str (str)
         {}
}
namespace
{
  NameToString::~ NameToString ()
         {}
}
namespace smtc
{
  util::String nameToString (NamePtr const & name)
  {
    util::String str;
    name->accept (NameToString (str));
    return str;
  }
}
#undef LZZ_INLINE
