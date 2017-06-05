// smtc_CreateVdfBlockDataScope.cpp
//

#include "smtc_CreateVdfBlockDataScope.h"
// semantic
#include "smtc_VdfBlockDataScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createVdfBlockDataScope (VdfDataFuncDefnPtr const & vdf_data_func_defn)
  {
    return new VdfBlockDataScope (vdf_data_func_defn);
  }
}
#undef LZZ_INLINE
