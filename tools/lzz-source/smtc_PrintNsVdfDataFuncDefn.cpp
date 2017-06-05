// smtc_PrintNsVdfDataFuncDefn.cpp
//

#include "smtc_PrintNsVdfDataFuncDefn.h"
// std lib
#include <algorithm>
 
// semantic
#include "smtc_GetNameLoc.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_NameToString.h"
#include "smtc_Obj.h"
#include "smtc_Output.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintFuncDecl.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_PrintObjDecl.h"
#include "smtc_VdfDataFuncDefn.h"

#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct PrintDataObj
  {
    FilePtr const & file;
    SectionKind skind;
    void operator () (ObjPtr const & obj) const;
  public:
    explicit PrintDataObj (FilePtr const & file, SectionKind skind);
    ~ PrintDataObj ();
  };
}
namespace
{
  struct PrintVdfDataFuncDefn : PrintFuncDecl
  {
    void print (FilePtr const & file, SectionKind skind, VdfDataFuncDefnPtr const & func_defn, NsPtr const & ns) const;
    void print (FilePtr const & file, SectionKind skind, VdfDataFuncDefnPtr const & func_defn) const;
  };
}
namespace
{
  void PrintDataObj::operator () (ObjPtr const & obj) const
  {
    PrintObjDecl printer;
    printer.with_init = true;
    printer.print (file, skind, obj);
  }
}
namespace
{
  LZZ_INLINE PrintDataObj::PrintDataObj (FilePtr const & file, SectionKind skind)
    : file (file), skind (skind)
       {}
}
namespace
{
  PrintDataObj::~ PrintDataObj ()
       {}
}
namespace
{
  void PrintVdfDataFuncDefn::print (FilePtr const & file, SectionKind skind, VdfDataFuncDefnPtr const & func_defn, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, func_defn);
      printNsClose (file, skind, ns_depth);
    }
}
namespace
{
  void PrintVdfDataFuncDefn::print (FilePtr const & file, SectionKind skind, VdfDataFuncDefnPtr const & func_defn) const
    {
      // declaration
      printLine (file, skind, getNameLoc (func_defn->getName ()), declToString (func_defn));
      printOpenBrace (file, skind);
      // objects 
      ObjPtrVector const & obj_set = func_defn->getObjSet ();
      if (! obj_set.empty ())
      {
        std::for_each (obj_set.begin (), obj_set.end (), PrintDataObj (file, skind));
        // comment -- obj set can not be empty (grammar)
        ObjPtr const & obj = obj_set.back ();
        printDir (file, skind, "#ifndef NDEBUG");
        util::String obj_name = nameToString (obj->getName ());
        util::String line = obj_name;
        line += "._cmt = \"";
        line += func_defn->getComment ();
        line += "\";";
        printLine (file, skind, line);
        printDir (file, skind, "#endif");
        // return stmt
        line = "return ";
        if (func_defn->hasReturnStmt ())
        {
          gram::Block const & ret_stmt = func_defn->getReturnStmt ();
          ret_stmt.trim ();
          line += ret_stmt.toString ();
          line += ';';
          printLine (file, skind, ret_stmt.getLoc (), line);
        }
        else
        {
          line += obj_name;
          line += ';';
          printLine (file, skind, line);
        }
      }
      printCloseBrace (file, skind);
    }
}
namespace smtc
{
  void printNsVdfDataFuncDefn (Output & out, VdfDataFuncDefnPtr const & func_defn, NsPtr const & ns)
  {
    bool is_decl = true;
    // declaration
    if (! isNsEnclUnmd (ns))
    {
      PrintFuncDecl printer;
      printer.is_decl = is_decl;
      printer.print (out.getHdrFile (), DECLARATION_SECTION, func_defn, ns);
      is_decl = false;
    }
    // definition
    PrintVdfDataFuncDefn printer;
    printer.is_decl = is_decl;
    printer.print (out.getSrcFile (), BODY_SECTION, func_defn, ns);
  }
}
#undef LZZ_INLINE
