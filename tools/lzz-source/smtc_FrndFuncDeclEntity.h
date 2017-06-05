// smtc_FrndFuncDeclEntity.h
//

#ifndef LZZ_smtc_FrndFuncDeclEntity_h
#define LZZ_smtc_FrndFuncDeclEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_FuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FrndFuncDeclEntity : public Entity
  {
    FuncDeclPtr m_func_decl;
  public:
    FrndFuncDeclEntity (FuncDeclPtr const & func_decl);
    ~ FrndFuncDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    FuncDeclPtr const & getFuncDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FrndFuncDeclEntity.inl"
#endif
#endif
