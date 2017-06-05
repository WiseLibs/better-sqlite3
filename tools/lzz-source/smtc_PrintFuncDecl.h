// smtc_PrintFuncDecl.h
//

#ifndef LZZ_smtc_PrintFuncDecl_h
#define LZZ_smtc_PrintFuncDecl_h
#include "smtc_FilePtr.h"
#include "smtc_FuncDeclPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_SectionKind.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintFuncDecl
  {
    NamePtr qual_name;
    bool is_frnd;
    bool is_inst;
    bool is_decl;
    bool not_inline;
    bool not_explicit;
    bool not_static;
    bool not_virtual;
    bool not_external;
    bool not_pure;
    bool use_alt_ret_type;
    PrintFuncDecl (NamePtr const & qual_name = NamePtr ());
    void print (FilePtr const & file, SectionKind skind, FuncDeclPtr const & func_decl, NsPtr const & ns) const;
    void print (FilePtr const & file, SectionKind skind, FuncDeclPtr const & func_decl) const;
  protected:
    util::String declToString (FuncDeclPtr const & func_decl) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintFuncDecl.inl"
#endif
#endif
