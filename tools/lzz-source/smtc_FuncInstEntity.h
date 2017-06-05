// smtc_FuncInstEntity.h
//

#ifndef LZZ_smtc_FuncInstEntity_h
#define LZZ_smtc_FuncInstEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_FuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncInstEntity : public Entity
  {
    FuncDeclPtr m_func_decl;
  public:
    FuncInstEntity (FuncDeclPtr const & func_decl);
    ~ FuncInstEntity ();
    void accept (EntityVisitor const & visitor) const;
    FuncDeclPtr const & getFuncDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FuncInstEntity.inl"
#endif
#endif
