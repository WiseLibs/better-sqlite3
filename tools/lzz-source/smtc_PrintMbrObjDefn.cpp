// smtc_PrintMbrObjDefn.cpp
//

#include "smtc_PrintMbrObjDefn.h"
// semantic
#include "smtc_IsObjStaticConstIntegral.h"
#include "smtc_Obj.h"
#include "smtc_Output.h"
#include "smtc_PrintObjDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrObjDefn (Output & out, ObjPtr const & obj, NsPtr const & ns, NamePtr const & qual_name)
  {
    // has definition only if static 
    if (obj->isStatic ())
    {
      PrintObjDecl printer (qual_name);
      printer.not_static = true;
      // if const integral then initializer with declaration
      if (! isObjConstIntegral (obj))
      {
        printer.with_init = true;
      }
      printer.print (out.getSrcFile (), BODY_SECTION, obj, ns);
    }
  }
}
#undef LZZ_INLINE
