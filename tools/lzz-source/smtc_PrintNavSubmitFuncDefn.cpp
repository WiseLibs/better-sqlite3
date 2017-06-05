// smtc_PrintNavSubmitFuncDefn.cpp
//

#include "smtc_PrintNavSubmitFuncDefn.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_GetNameLoc.h"
#include "smtc_NameToString.h"
#include "smtc_NavSubmitFuncDefn.h"
#include "smtc_Obj.h"
#include "smtc_Output.h"
#include "smtc_Param.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintFuncDecl.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_PrintObjDecl.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct PrintNavSubmitFuncDefn : PrintFuncDecl
  {
    void print (FilePtr const & file, SectionKind skind, NavSubmitFuncDefnPtr const & func_defn, NsPtr const & ns) const;
    void print (FilePtr const & file, SectionKind skind, NavSubmitFuncDefnPtr const & func_defn) const;
    struct PrintSubmitObj
    {
      FilePtr const & file;
      SectionKind skind;
      void operator () (ObjPtr const & obj) const;
    public:
      explicit PrintSubmitObj (FilePtr const & file, SectionKind skind);
      ~ PrintSubmitObj ();
    };
    template <typename T>
    struct AppendName
    {
      util::String & str;
      bool & first;
      void operator () (T const & t);
    public:
      explicit AppendName (util::String & str, bool & first);
      ~ AppendName ();
    };
  public:
    explicit PrintNavSubmitFuncDefn (NamePtr const & qual_name);
    ~ PrintNavSubmitFuncDefn ();
  };
}
namespace
{
  void PrintNavSubmitFuncDefn::print (FilePtr const & file, SectionKind skind, NavSubmitFuncDefnPtr const & func_defn, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, func_defn);
      printNsClose (file, skind, ns_depth);
    }
}
namespace
{
  void PrintNavSubmitFuncDefn::print (FilePtr const & file, SectionKind skind, NavSubmitFuncDefnPtr const & func_defn) const
    {
      printLine (file, skind, getNameLoc (func_defn->getName ()), declToString (func_defn));
      printOpenBrace (file, skind);
      // object definitions
      ObjPtrVector const & obj_set = func_defn->getObjSet ();
      std::for_each (obj_set.begin (), obj_set.end (), PrintSubmitObj (file, skind));
      // navigate call
      ParamPtrVector const & param_set = func_defn->getParamSet ();
      util::String str = nameToString (param_set.front ()->getName ());
      str += ".navigate (";
      NamePtr const & nav_name = func_defn->getNavName ();
      str += nameToString (nav_name);
      str += " (";
      // params are next, minus node param
      bool first = true;
      std::for_each (param_set.begin () + 1, param_set.end (), AppendName <ParamPtr> (str, first));
      // then objects
      std::for_each (obj_set.begin (), obj_set.end (), AppendName <ObjPtr> (str, first));
      str += "));";
      printLine (file, skind, getNameLoc (nav_name), str);
      // return stmt
      gram::Block const & ret_stmt = func_defn->getReturnStmt ();
      if (ret_stmt.isSet ())
      {
        str = "return";
        str += ret_stmt.toString ();
        str += ';';
        printLine (file, skind, ret_stmt.getLoc (), str);
      }
      printCloseBrace (file, skind);

    }
}
namespace
{
  void PrintNavSubmitFuncDefn::PrintSubmitObj::operator () (ObjPtr const & obj) const
    {
      PrintObjDecl printer;
      printer.with_init = true;
      printer.print (file, skind, obj);
    }
}
namespace
{
  LZZ_INLINE PrintNavSubmitFuncDefn::PrintSubmitObj::PrintSubmitObj (FilePtr const & file, SectionKind skind)
    : file (file), skind (skind)
         {}
}
namespace
{
  PrintNavSubmitFuncDefn::PrintSubmitObj::~ PrintSubmitObj ()
         {}
}
namespace
{
  template <typename T>
  void PrintNavSubmitFuncDefn::AppendName <T>::operator () (T const & t)
    {
      if (first)
      {
        first = false;
      }
      else
      {
        str += ", ";
      }
      str += nameToString (t->getName ());
    }
}
namespace
{
  template <typename T>
  LZZ_INLINE PrintNavSubmitFuncDefn::AppendName <T>::AppendName (util::String & str, bool & first)
    : str (str), first (first)
         {}
}
namespace
{
  template <typename T>
  PrintNavSubmitFuncDefn::AppendName <T>::~ AppendName ()
         {}
}
namespace
{
  LZZ_INLINE PrintNavSubmitFuncDefn::PrintNavSubmitFuncDefn (NamePtr const & qual_name)
    : PrintFuncDecl (qual_name)
         {}
}
namespace
{
  PrintNavSubmitFuncDefn::~ PrintNavSubmitFuncDefn ()
         {}
}
namespace smtc
{
  void printNavSubmitFuncDefn (Output & out, NavSubmitFuncDefnPtr const & func_defn, NsPtr const & ns, NamePtr const & qual_name)
  {
    PrintNavSubmitFuncDefn printer (qual_name);
    printer.not_static = true;
    printer.print (out.getSrcFile (), BODY_SECTION, func_defn, ns);
  }
}
#undef LZZ_INLINE
