// smtc_PrintMbrTmplObjDefn.cpp
//

#include "smtc_PrintMbrTmplObjDefn.h"
// semantic
#include "smtc_IsExplicitTmplSpec.h"
#include "smtc_IsNsEnclUnmd.h"
#include "smtc_IsObjStaticConstIntegral.h"
#include "smtc_Obj.h"
#include "smtc_Output.h"
#include "smtc_PrintTmplObjDefn.h"

// config
#include "conf_Config.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrTmplObjDefn (Output & out, ObjPtr const & obj, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name)
  {
    if (obj->isStatic ())
    {
      // get file
      FilePtr file;
      if (conf::getOptionValue (conf::opt_tpl_src) || isNsEnclUnmd (ns) || isExplicitTmplSpec (tmpl_spec_set))
      {
        file = out.getSrcFile ();
      }
      else if (conf::getOptionValue (conf::opt_tpl))
      {
        file = out.getTplFile ();
      }
      else
      {
        file = out.getHdrFile ();
      }
      PrintTmplObjDefn printer (qual_name);
      printer.not_static = true;
      // if const integral then initializer with declaration
      printer.with_init = ! isObjConstIntegral (obj);
      printer.print (file, BODY_SECTION, obj, tmpl_spec_set, ns);
    }
  }
}
#undef LZZ_INLINE
