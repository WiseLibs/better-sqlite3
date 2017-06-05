// smtc_PrintUsingDecl.h
//

#ifndef LZZ_smtc_PrintUsingDecl_h
#define LZZ_smtc_PrintUsingDecl_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_SectionKind.h"
#include "smtc_UsingDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printUsingDecl (FilePtr const & file, SectionKind skind, UsingDeclPtr const & using_decl, NsPtr const & ns);
}
namespace smtc
{
  void printUsingDecl (FilePtr const & file, SectionKind skind, UsingDeclPtr const & using_decl);
}
#undef LZZ_INLINE
#endif
