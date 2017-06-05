// smtc_CreateOperBaseName.h
//

#ifndef LZZ_smtc_CreateOperBaseName_h
#define LZZ_smtc_CreateOperBaseName_h
// semantic
#include "smtc_BaseNamePtr.h"
#include "smtc_OperKind.h"

// util
#include "util_Loc.h"
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseNamePtr createOperBaseName (util::Loc const & loc, OperKind oper_kind);
}
namespace smtc
{
  BaseNamePtr createOperBaseName (util::Loc const & loc, util::Ident const & macro, OperKind oper_kind);
}
#undef LZZ_INLINE
#endif
