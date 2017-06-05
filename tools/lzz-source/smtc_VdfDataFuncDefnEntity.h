// smtc_VdfDataFuncDefnEntity.h
//

#ifndef LZZ_smtc_VdfDataFuncDefnEntity_h
#define LZZ_smtc_VdfDataFuncDefnEntity_h
// semantic
#include "smtc_FuncDeclEntity.h"
#include "smtc_VdfDataFuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class VdfDataFuncDefnEntity : public FuncDeclEntity
  {
  public:
    VdfDataFuncDefnEntity (VdfDataFuncDefnPtr const & vdf_data_func_defn);
    ~ VdfDataFuncDefnEntity ();
    void accept (EntityVisitor const & visitor) const;
    VdfDataFuncDefnPtr getVdfDataFuncDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_VdfDataFuncDefnEntity.inl"
#endif
#endif
