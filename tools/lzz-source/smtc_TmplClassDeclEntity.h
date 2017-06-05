// smtc_TmplClassDeclEntity.h
//

#ifndef LZZ_smtc_TmplClassDeclEntity_h
#define LZZ_smtc_TmplClassDeclEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_TmplClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplClassDeclEntity : public Entity
  {
    TmplClassDeclPtr m_tmpl_class_decl;
  public:
    TmplClassDeclEntity (TmplClassDeclPtr const & tmpl_class_decl);
    ~ TmplClassDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    TmplClassDeclPtr const & getTmplClassDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplClassDeclEntity.inl"
#endif
#endif
