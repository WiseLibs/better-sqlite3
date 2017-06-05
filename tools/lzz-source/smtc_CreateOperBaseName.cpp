// smtc_CreateOperBaseName.cpp
//

#include "smtc_CreateOperBaseName.h"
// semantic
#include "smtc_OperBaseName.h"
#define LZZ_INLINE inline
namespace smtc
{
  BaseNamePtr createOperBaseName (util::Loc const & loc, OperKind oper_kind)
  {
    return createOperBaseName (loc, util::Ident (), oper_kind); 
  }
}
namespace smtc
{
  BaseNamePtr createOperBaseName (util::Loc const & loc, util::Ident const & macro, OperKind oper_kind)
  {
    return new OperBaseName (loc, macro, oper_kind);
  }
}
#undef LZZ_INLINE
