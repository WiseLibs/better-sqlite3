// smtc_FrndFuncDefnEntity.h
//

#ifndef LZZ_smtc_FrndFuncDefnEntity_h
#define LZZ_smtc_FrndFuncDefnEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_FuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FrndFuncDefnEntity : public Entity
  {
    FuncDefnPtr m_func_defn;
  public:
    FrndFuncDefnEntity (FuncDefnPtr const & func_defn);
    ~ FrndFuncDefnEntity ();
    void accept (EntityVisitor const & visitor) const;
    FuncDefnPtr const & getFuncDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FrndFuncDefnEntity.inl"
#endif
#endif
