// smtc_CreateUsingDecl.h
//

#ifndef LZZ_smtc_CreateUsingDecl_h
#define LZZ_smtc_CreateUsingDecl_h
// semantic
#include "smtc_UsingDeclPtr.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  UsingDeclPtr createUsingDecl (NamePtr const & name);
}
#undef LZZ_INLINE
#endif
