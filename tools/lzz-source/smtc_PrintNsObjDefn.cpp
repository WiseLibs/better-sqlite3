// smtc_PrintNsObjDefn.cpp
//

#include "smtc_PrintNsObjDefn.h"
// semantic
#include "smtc_IsNameQual.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_Obj.h"
#include "smtc_Output.h"
#include "smtc_PrintObjDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printNsObjDefn (Output & out, ObjPtr const & obj, NsPtr const & ns)
  {
    // assume has_decl (in header) and has_defn (in source)
    bool has_decl = true;
    bool has_defn = true;
    bool is_qual = isNameQual (obj->getName ());
    if (obj->isStatic () || isNsEnclUnmd (ns))
    {
      // no decl in header file
      has_decl = false;
    }
    else if (obj->isExtern () || obj->hasLinkage ())
    {
      // obj declaration if no init
      has_defn = obj->hasInit ();
      // has decl in hdr file unless qualified defn
      has_decl = ! (has_defn && is_qual);
    }
    else
    {
      // this is an obj definition.  has decl in hdr file if neither explicitly const nor qualified
      has_decl = ! (obj->getCvType ().getCv ().isConstOnly () || is_qual);
    }
    if (has_decl)
    {
      PrintObjDecl printer;
      // if the obj has linkage then don't use 'extern'
      printer.is_extern = ! obj->hasLinkage ();
      printer.print (out.getHdrFile (), DECLARATION_SECTION, obj, ns);
    }
    if (has_defn)
    {
      PrintObjDefn printer;
      // don't need extern if had (extern) decl
      printer.not_extern = has_decl;
      // output to body if has decl in header file
      // we'll output to declaration section otherwise because we must introduce the name of the object 
      printer.print (out.getSrcFile (), has_decl ? BODY_SECTION : DECLARATION_SECTION, obj, ns);
    }
  }
}
#undef LZZ_INLINE
