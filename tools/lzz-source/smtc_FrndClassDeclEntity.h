// smtc_FrndClassDeclEntity.h
//

#ifndef LZZ_smtc_FrndClassDeclEntity_h
#define LZZ_smtc_FrndClassDeclEntity_h
// semantic
#include "smtc_ClassDeclPtr.h"
#include "smtc_Entity.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FrndClassDeclEntity : public Entity
  {
    ClassDeclPtr m_class_decl;
  public:
    FrndClassDeclEntity (ClassDeclPtr const & class_decl);
    ~ FrndClassDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    ClassDeclPtr const & getClassDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FrndClassDeclEntity.inl"
#endif
#endif
