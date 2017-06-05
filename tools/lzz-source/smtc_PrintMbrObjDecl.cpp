// smtc_PrintMbrObjDecl.cpp
//

#include "smtc_PrintMbrObjDecl.h"
// semantic
#include "smtc_IsObjStaticConstIntegral.h"
#include "smtc_PrintObjDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printMbrObjDecl (FilePtr const & file, ObjPtr const & obj)
  {
    PrintObjDecl printer;
    // print initializer if static const integral obj
    if (isObjStaticConstIntegral (obj))
    {
      printer.with_init = true;
    }
    printer.print (file, DECLARATION_SECTION, obj);
  }
}
#undef LZZ_INLINE
