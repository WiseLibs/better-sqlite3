// smtc_FuncDeclEntity.h
//

#ifndef LZZ_smtc_FuncDeclEntity_h
#define LZZ_smtc_FuncDeclEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_FuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncDeclEntity : public Entity
  {
    FuncDeclPtr m_func_decl;
  public:
    FuncDeclEntity (FuncDeclPtr const & func_decl);
    ~ FuncDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    FuncDeclPtr const & getFuncDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FuncDeclEntity.inl"
#endif
#endif
