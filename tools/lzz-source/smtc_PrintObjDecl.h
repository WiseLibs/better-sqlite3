// smtc_PrintObjDecl.h
//

#ifndef LZZ_smtc_PrintObjDecl_h
#define LZZ_smtc_PrintObjDecl_h
#include "smtc_FilePtr.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_ObjPtr.h"
#include "smtc_SectionKind.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintObjDecl
  {
    NamePtr qual_name;
    bool is_extern;
    bool not_extern;
    bool not_static;
    bool with_init;
    PrintObjDecl (NamePtr const & qual_name = NamePtr ());
    void print (FilePtr const & file, SectionKind skind, ObjPtr const & obj, NsPtr const & ns) const;
    void print (FilePtr const & file, SectionKind skind, ObjPtr const & obj) const;
  protected:
    util::String declToString (ObjPtr const & obj) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintObjDecl.inl"
#endif
#endif
