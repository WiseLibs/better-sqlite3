// smtc_PrintFuncDefn.h
//

#ifndef LZZ_smtc_PrintFuncDefn_h
#define LZZ_smtc_PrintFuncDefn_h
// semantic
#include "smtc_FuncDefnPtr.h"
#include "smtc_PrintFuncDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintFuncDefn : public PrintFuncDecl
  {
    PrintFuncDefn (NamePtr const & qual_name = NamePtr ());
    void print (FilePtr const & file, SectionKind skind, FuncDefnPtr const & func_defn, NsPtr const & ns) const;
    void print (FilePtr const & file, SectionKind skind, FuncDefnPtr const & func_defn) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintFuncDefn.inl"
#endif
#endif
