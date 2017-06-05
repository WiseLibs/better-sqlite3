// smtc_PrintTmplObjDefn.cpp
//

#include "smtc_PrintTmplObjDefn.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintTmplObjDefn.inl"
#endif
// semantic
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_PrintTmplSpecSet.h"
#define LZZ_INLINE inline
namespace smtc
{
  void PrintTmplObjDefn::print (FilePtr const & file, SectionKind skind, ObjPtr const & obj, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, obj, tmpl_spec_set);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintTmplObjDefn::print (FilePtr const & file, SectionKind skind, ObjPtr const & obj, TmplSpecPtrVector const & tmpl_spec_set) const
    {
      printTmplSpecSet (file, skind, tmpl_spec_set, false);
      PrintObjDefn::print (file, skind, obj);
    }
}
#undef LZZ_INLINE
