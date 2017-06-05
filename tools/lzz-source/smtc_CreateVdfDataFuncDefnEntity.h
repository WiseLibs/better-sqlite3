// smtc_CreateVdfDataFuncDefnEntity.h
//

#ifndef LZZ_smtc_CreateVdfDataFuncDefnEntity_h
#define LZZ_smtc_CreateVdfDataFuncDefnEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_VdfDataFuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createVdfDataFuncDefnEntity (VdfDataFuncDefnPtr const & vdf_data_func_defn);
}
#undef LZZ_INLINE
#endif
