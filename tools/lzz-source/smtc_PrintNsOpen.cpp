// smtc_PrintNsOpen.cpp
//

#include "smtc_PrintNsOpen.h"
// semantic
#include "smtc_BaseNameToString.h"
#include "smtc_IdentBaseName.h"
#include "smtc_LinkageNs.h"
#include "smtc_NameVisitor.h"
#include "smtc_NamedNs.h"
#include "smtc_NonTmplName.h"
#include "smtc_NsVisitor.h"
#include "smtc_PrintCode.h"
#include "smtc_QualName.h"
#include "smtc_UnnamedNs.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  using namespace util;
}
namespace
{
  void printNsName (FilePtr const & file, Loc const & loc, String const & name = String ());
}
namespace
{
  struct PrintNsName : NameVisitor
  {
    FilePtr const & file;
    SectionKind skind;
    int & depth;
    void visit (QualName const & name) const;
    void visit (NonTmplName const & name) const;
  public:
    explicit PrintNsName (FilePtr const & file, SectionKind skind, int & depth);
    ~ PrintNsName ();
  };
}
namespace
{
  struct PrintNsOpen : NsVisitor
  {
    FilePtr const & file;
    SectionKind skind;
    int & depth;
    void visit (GlobalNs const & ns) const;
    void visit (NamedNs const & ns) const;
    void visit (UnnamedNs const & ns) const;
    void visit (LinkageNs const & ns) const;
    void visitEnclNs (NestedNs const & ns) const;
  public:
    explicit PrintNsOpen (FilePtr const & file, SectionKind skind, int & depth);
    ~ PrintNsOpen ();
  };
}
namespace
{
  void printNsName (FilePtr const & file, Loc const & loc, String const & name)
  {}
}
namespace
{
  void PrintNsName::visit (QualName const & name) const
    {
      name.getQualName ()->accept (* this);
      name.getUnqlName ()->accept (* this);
    }
}
namespace
{
  void PrintNsName::visit (NonTmplName const & name) const
    {
      using namespace util;
      BaseNamePtr const & base_name = name.getBaseName ();
      String line = "namespace";
      appendWithSpace (line, baseNameToString (base_name));
      printLine (file, skind, base_name->getLoc (), line);
      printOpenBrace (file, skind);
      ++ depth;
    }
}
namespace
{
  LZZ_INLINE PrintNsName::PrintNsName (FilePtr const & file, SectionKind skind, int & depth)
    : NameVisitor (), file (file), skind (skind), depth (depth)
         {}
}
namespace
{
  PrintNsName::~ PrintNsName ()
         {}
}
namespace
{
  void PrintNsOpen::visit (GlobalNs const & ns) const
    {
      depth = 0;
    }
}
namespace
{
  void PrintNsOpen::visit (NamedNs const & ns) const
    {
      visitEnclNs (ns);
      ns.getName ()->accept (PrintNsName (file, skind, depth));
    }
}
namespace
{
  void PrintNsOpen::visit (UnnamedNs const & ns) const
    {
      using namespace util;
      visitEnclNs (ns);
      printLine (file, skind, ns.getLoc (), "namespace");
      printOpenBrace (file, skind);
      ++ depth;
    }
}
namespace
{
  void PrintNsOpen::visit (LinkageNs const & ns) const
    {
      using namespace util;
      visitEnclNs (ns);
      String line = "extern";
      appendWithSpace (line, ns.getLinkage ().c_str ());
      printLine (file, skind, ns.getLoc (), line);
      printOpenBrace (file, skind);
      ++ depth;
    }
}
namespace
{
  LZZ_INLINE void PrintNsOpen::visitEnclNs (NestedNs const & ns) const
    {
      ns.getEnclNs ()->accept (* this);
    }
}
namespace
{
  LZZ_INLINE PrintNsOpen::PrintNsOpen (FilePtr const & file, SectionKind skind, int & depth)
    : NsVisitor (), file (file), skind (skind), depth (depth)
         {}
}
namespace
{
  PrintNsOpen::~ PrintNsOpen ()
         {}
}
namespace smtc
{
  int printNsOpen (FilePtr const & file, SectionKind skind, NsPtr const & ns)
  {
    int depth = 0;
    ns->accept (PrintNsOpen (file, skind, depth));
    return depth;
  }
}
namespace smtc
{
  int printNsOpenIfSet (FilePtr const & file, SectionKind skind, NsPtr const & ns)
  {
    int depth = 0;
    if (ns.isSet ())
    {
      depth = printNsOpen (file, skind, ns);
    }
    return depth;
  }
}
#undef LZZ_INLINE
