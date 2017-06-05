// smtc_CreateFuncInstEntity.h
//

#ifndef LZZ_smtc_CreateFuncInstEntity_h
#define LZZ_smtc_CreateFuncInstEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_FuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFuncInstEntity (FuncDeclPtr const & func_decl);
}
#undef LZZ_INLINE
#endif
