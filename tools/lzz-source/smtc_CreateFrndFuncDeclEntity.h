// smtc_CreateFrndFuncDeclEntity.h
//

#ifndef LZZ_smtc_CreateFrndFuncDeclEntity_h
#define LZZ_smtc_CreateFrndFuncDeclEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_FuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndFuncDeclEntity (FuncDeclPtr const & func_decl);
}
#undef LZZ_INLINE
#endif
