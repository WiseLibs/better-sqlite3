// smtc_NavSubmitFuncDefnEntity.h
//

#ifndef LZZ_smtc_NavSubmitFuncDefnEntity_h
#define LZZ_smtc_NavSubmitFuncDefnEntity_h
// semantic
#include "smtc_FuncDeclEntity.h"
#include "smtc_NavSubmitFuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NavSubmitFuncDefnEntity : public FuncDeclEntity
  {
  public:
    NavSubmitFuncDefnEntity (NavSubmitFuncDefnPtr const & nav_submit_func_defn);
    ~ NavSubmitFuncDefnEntity ();
    void accept (EntityVisitor const & visitor) const;
    NavSubmitFuncDefnPtr getNavSubmitFuncDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NavSubmitFuncDefnEntity.inl"
#endif
#endif
