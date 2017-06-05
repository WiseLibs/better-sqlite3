// smtc_PrintObjDefn.h
//

#ifndef LZZ_smtc_PrintObjDefn_h
#define LZZ_smtc_PrintObjDefn_h
// semantic
#include "smtc_PrintObjDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintObjDefn : PrintObjDecl
  {
    PrintObjDefn (NamePtr const & qual_name = NamePtr ());
    void print (FilePtr const & file, SectionKind skind, ObjPtr const & obj, NsPtr const & ns) const;
    void print (FilePtr const & file, SectionKind skind, ObjPtr const & obj) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintObjDefn.inl"
#endif
#endif
