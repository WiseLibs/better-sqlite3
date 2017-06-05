// smtc_FrndTmplClassDeclEntity.h
//

#ifndef LZZ_smtc_FrndTmplClassDeclEntity_h
#define LZZ_smtc_FrndTmplClassDeclEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_TmplClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FrndTmplClassDeclEntity : public Entity
  {
    TmplClassDeclPtr m_tmpl_class_decl;
  public:
    FrndTmplClassDeclEntity (TmplClassDeclPtr const & tmpl_class_decl);
    ~ FrndTmplClassDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    TmplClassDeclPtr const & getTmplClassDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FrndTmplClassDeclEntity.inl"
#endif
#endif
