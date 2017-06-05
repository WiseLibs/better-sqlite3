// smtc_FrndTmplFuncDeclEntity.h
//

#ifndef LZZ_smtc_FrndTmplFuncDeclEntity_h
#define LZZ_smtc_FrndTmplFuncDeclEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_TmplFuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FrndTmplFuncDeclEntity : public Entity
  {
    TmplFuncDeclPtr m_tmpl_func_decl;
  public:
    FrndTmplFuncDeclEntity (TmplFuncDeclPtr const & tmpl_func_decl);
    ~ FrndTmplFuncDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    TmplFuncDeclPtr const & getTmplFuncDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FrndTmplFuncDeclEntity.inl"
#endif
#endif
