// smtc_PrintFuncDecl.cpp
//

#include "smtc_PrintFuncDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintFuncDecl.inl"
#endif
#include "conf_Config.h"
#include "smtc_AppendCv.h"
#include "smtc_CreateQualName.h"
#include "smtc_File.h"
#include "smtc_FuncDecl.h"
#include "smtc_GetNameLoc.h"
#include "smtc_NameToString.h"
#include "smtc_ParamSetToString.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_SectionKind.h"
#include "smtc_SpecFlags.h"
#include "smtc_SpecFlagsToString.h"
#include "smtc_ThrowSpecToString.h"
#include "util_AppendWithSpace.h"
#include "util_BitOp.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  void PrintFuncDecl::print (FilePtr const & file, SectionKind skind, FuncDeclPtr const & func_decl, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, func_decl);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintFuncDecl::print (FilePtr const & file, SectionKind skind, FuncDeclPtr const & func_decl) const
    {
      String str = declToString (func_decl);
      str += ';';
      printLine (file, skind, getNameLoc (func_decl->getName ()), str);
    }
}
namespace smtc
{
  util::String PrintFuncDecl::declToString (FuncDeclPtr const & func_decl) const
    {
      String str;
      if (is_inst)
      {
        appendWithSpace (str, "template");
      }
      Linkage const & linkage = func_decl->getLinkage ();
      if (linkage.isSet ())
      {
        appendWithSpace (str, "extern");
        appendWithSpace (str, linkage.getLanguage ().c_str ());
      }
      if (is_frnd)
      {
        appendWithSpace (str, "friend");
      }
      int flags = func_decl->getFlags ();
      if (hasFlag (flags, DLL_API_SPEC))
      {
        appendWithSpace (str, conf::getOptionValue (conf::opt_dll_api));
      }
      else if (hasFlag (flags, EXTERN_SPEC))
      {
        appendWithSpace (str, "extern");
      }
      if (! not_inline && hasFlag (flags, INLINE_SPEC))
      {
        appendWithSpace (str, "LZZ_INLINE");
      }
      if (! not_virtual && hasFlag (flags, VIRTUAL_SPEC))
      {
        appendWithSpace (str, "virtual");
      }
      if (! not_explicit && hasFlag (flags, EXPLICIT_SPEC))
      {
        appendWithSpace (str, "explicit");
      }
      if (! not_static && hasFlag (flags, STATIC_SPEC))
      {
        appendWithSpace (str, "static");
      }
      NamePtr name = func_decl->getName ();
      if (qual_name.isSet ())
      {
        name = createQualName (qual_name, name);
      }
      String dcl_str = nameToString (name);
      appendWithSpace (dcl_str, '(');
      ParamPtrVector const & param_set = func_decl->getParamSet ();
      dcl_str += paramSetToString (param_set, is_decl);
      if (func_decl->hasVarArg ())
      {
        if (! param_set.empty ())
        {
          dcl_str += ", ";
        }
        dcl_str += "...";
      }
      dcl_str += ')';
      appendCv (dcl_str, func_decl->getCv ());
      ThrowSpecPtr const & throw_spec = func_decl->getThrowSpec ();
      if (throw_spec.isSet ())
      {
        appendWithSpace (dcl_str, throwSpecToString (throw_spec));
      }
      CvType const & ret_type = (use_alt_ret_type && func_decl->hasAltReturnType ()) ? func_decl->getAltReturnType () : func_decl->getReturnType ();
      if (ret_type.isSet ())
      {
        dcl_str = ret_type.toString (dcl_str);
      }
      appendWithSpace (str, dcl_str);
      if (! not_pure && func_decl->isPure ())
      {
        appendWithSpace (str, "= 0");
      }
      return str;
    }
}
#undef LZZ_INLINE
