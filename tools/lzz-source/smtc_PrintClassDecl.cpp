// smtc_PrintClassDecl.cpp
//

#include "smtc_PrintClassDecl.h"
#include "conf_Config.h"
#include "smtc_ClassDecl.h"
#include "smtc_ClassKeyToString.h"
#include "smtc_File.h"
#include "smtc_GetNameLoc.h"
#include "smtc_NameToString.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  PrintClassDecl::PrintClassDecl ()
    : is_frnd (false), is_inst (false), is_inst_extern (false), skind (DECLARATION_SECTION)
    {}
}
namespace smtc
{
  void PrintClassDecl::print (FilePtr const & file, ClassDeclPtr const & class_decl, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, class_decl);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintClassDecl::print (FilePtr const & file, ClassDeclPtr const & class_decl) const
    {
      // instantiation extern only if dll_api macro is set
      bool has_exports = is_inst && is_inst_extern && conf::isOptionSet (conf::opt_dll_api);
      if (has_exports)
      {
        // we know dll_exports macro is set if dll_api macro is set
        file->getStream (skind) << "#ifndef " << conf::getOptionValue (conf::opt_dll_exports) << '\n';
      }
      String str = declToString (class_decl);
      str += ';';
      printLine (file, skind, getNameLoc (class_decl->getName ()), str);
      if (has_exports)
      {
        file->getStream (skind) << "#endif" << '\n';
      }
    }
}
namespace smtc
{
  util::String PrintClassDecl::declToString (ClassDeclPtr const & class_decl) const
    {
      String str;
      if (is_inst)
      {
        // extern only if dll_api is set
        if (is_inst_extern && conf::isOptionSet (conf::opt_dll_api))
        {
          str = "extern ";
        }
        str += "template";
      }
      else if (is_frnd)
      {
        str =  "friend";
      }
      appendWithSpace (str, classKeyToString (class_decl->getKey ()));
      if (class_decl->isDllApi ())
      {
        appendWithSpace (str, conf::getOptionValue (conf::opt_dll_api));
      }
      appendWithSpace (str, nameToString (class_decl->getName ()));
      return str;
    }
}
#undef LZZ_INLINE
