// smtc_CreateFuncDeclEntity.h
//

#ifndef LZZ_smtc_CreateFuncDeclEntity_h
#define LZZ_smtc_CreateFuncDeclEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_FuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFuncDeclEntity (FuncDeclPtr const & func_decl);
}
#undef LZZ_INLINE
#endif
