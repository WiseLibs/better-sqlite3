// smtc_CreateVdfDataFuncDefnEntity.cpp
//

#include "smtc_CreateVdfDataFuncDefnEntity.h"
// semantic
#include "smtc_VdfDataFuncDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createVdfDataFuncDefnEntity (VdfDataFuncDefnPtr const & vdf_data_func_defn)
  {
    return new VdfDataFuncDefnEntity (vdf_data_func_defn);
  }
}
#undef LZZ_INLINE
