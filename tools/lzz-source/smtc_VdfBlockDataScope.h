// smtc_VdfBlockDataScope.h
//

#ifndef LZZ_smtc_VdfBlockDataScope_h
#define LZZ_smtc_VdfBlockDataScope_h
// semantic
#include "smtc_Scope.h"
#include "smtc_VdfDataFuncDefnPtr.h"

#define LZZ_INLINE inline
namespace smtc
{
  class VdfBlockDataScope : public Scope
  {
    VdfDataFuncDefnPtr m_vdf_data_func_defn;
  public:
    VdfBlockDataScope (VdfDataFuncDefnPtr const & vdf_data_func_defn);
    ~ VdfBlockDataScope ();
    void accept (ScopeVisitor const & visitor) const;
    VdfDataFuncDefnPtr const & getVdfDataFuncDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_VdfBlockDataScope.inl"
#endif
#endif
