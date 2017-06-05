// smtc_PrintTmplObjDefn.h
//

#ifndef LZZ_smtc_PrintTmplObjDefn_h
#define LZZ_smtc_PrintTmplObjDefn_h
// semantic
#include "smtc_PrintObjDefn.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintTmplObjDefn : PrintObjDefn
  {
    PrintTmplObjDefn (NamePtr const & qual_name = NamePtr ());
    void print (FilePtr const & file, SectionKind skind, ObjPtr const & obj, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns) const;
    void print (FilePtr const & file, SectionKind skind, ObjPtr const & obj, TmplSpecPtrVector const & tmpl_spec_set) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintTmplObjDefn.inl"
#endif
#endif
