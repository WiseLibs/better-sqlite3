// smtc_PrintClassDecl.h
//

#ifndef LZZ_smtc_PrintClassDecl_h
#define LZZ_smtc_PrintClassDecl_h
#include "smtc_ClassDeclPtr.h"
#include "smtc_FilePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_SectionKind.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintClassDecl
  {
    bool is_frnd;
    bool is_inst;
    bool is_inst_extern;
    SectionKind const skind;
    PrintClassDecl ();
    void print (FilePtr const & file, ClassDeclPtr const & class_decl, NsPtr const & ns) const;
    void print (FilePtr const & file, ClassDeclPtr const & class_decl) const;
  protected:
    util::String declToString (ClassDeclPtr const & class_decl) const;
  };
}
#undef LZZ_INLINE
#endif
