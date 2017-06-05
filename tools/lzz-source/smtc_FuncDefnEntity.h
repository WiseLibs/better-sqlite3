// smtc_FuncDefnEntity.h
//

#ifndef LZZ_smtc_FuncDefnEntity_h
#define LZZ_smtc_FuncDefnEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_FuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncDefnEntity : public Entity
  {
    FuncDefnPtr m_func_defn;
  public:
    FuncDefnEntity (FuncDefnPtr const & func_defn);
    ~ FuncDefnEntity ();
    void accept (EntityVisitor const & visitor) const;
    FuncDefnPtr const & getFuncDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FuncDefnEntity.inl"
#endif
#endif
