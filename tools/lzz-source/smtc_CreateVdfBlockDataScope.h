// smtc_CreateVdfBlockDataScope.h
//

#ifndef LZZ_smtc_CreateVdfBlockDataScope_h
#define LZZ_smtc_CreateVdfBlockDataScope_h
// semantic
#include "smtc_ScopePtr.h"
#include "smtc_VdfDataFuncDefnPtr.h"

#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createVdfBlockDataScope (VdfDataFuncDefnPtr const & vdf_data_func_defn);
}
#undef LZZ_INLINE
#endif
