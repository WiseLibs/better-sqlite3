// smtc_PrintObjDecl.cpp
//

#include "smtc_PrintObjDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintObjDecl.inl"
#endif
#include "conf_Config.h"
#include "smtc_CreateQualName.h"
#include "smtc_File.h"
#include "smtc_GetNameLoc.h"
#include "smtc_Init.h"
#include "smtc_NameToString.h"
#include "smtc_Obj.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_SpecFlags.h"
#include "util_AppendWithSpace.h"
#include "util_BitOp.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  void PrintObjDecl::print (FilePtr const & file, SectionKind skind, ObjPtr const & obj, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, obj);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintObjDecl::print (FilePtr const & file, SectionKind skind, ObjPtr const & obj) const
    {
      printHashLine (file, skind, getNameLoc (obj->getName ()));
      std::ostream & os = file->indent (skind) << declToString (obj);
      if (with_init && obj->hasInit ())
      {
        os << ' ';
        obj->getInit ()->print (file, skind);
      }
      os << ';' << '\n';
    }
}
namespace smtc
{
  util::String PrintObjDecl::declToString (ObjPtr const & obj) const
    {
      String str;
      Linkage const & linkage = obj->getLinkage ();
      if (linkage.isSet ())
      {
        appendWithSpace (str, "extern");
        appendWithSpace (str, linkage.getLanguage ().c_str ());
      }
      int flags = obj->getFlags ();
      if (! not_extern)
      {
        if (is_extern || hasFlag (flags, EXTERN_SPEC))
        {
          appendWithSpace (str, "extern");
        }
      }
      if (hasFlag (flags, DLL_API_SPEC))
      {
        appendWithSpace (str, conf::getOptionValue (conf::opt_dll_api));
      }
      if (! not_static && hasFlag (flags, STATIC_SPEC))
      {
        appendWithSpace (str, "static");
      }
      if (hasFlag (flags, MUTABLE_SPEC))
      {
        appendWithSpace (str, "mutable");
      }
      NamePtr name = obj->getName ();
      if (qual_name.isSet ())
      {
        name = createQualName (qual_name, name);
      }
      String dcl_str = nameToString (name);
      appendWithSpace (str, obj->getCvType ().toString (dcl_str));
      return str;
    }
}
#undef LZZ_INLINE
