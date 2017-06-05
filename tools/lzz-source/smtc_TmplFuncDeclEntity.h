// smtc_TmplFuncDeclEntity.h
//

#ifndef LZZ_smtc_TmplFuncDeclEntity_h
#define LZZ_smtc_TmplFuncDeclEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_TmplFuncDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplFuncDeclEntity : public Entity
  {
    TmplFuncDeclPtr m_tmpl_func_decl;
  public:
    TmplFuncDeclEntity (TmplFuncDeclPtr const & tmpl_func_decl);
    ~ TmplFuncDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    TmplFuncDeclPtr const & getTmplFuncDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplFuncDeclEntity.inl"
#endif
#endif
