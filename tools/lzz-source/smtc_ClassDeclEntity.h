// smtc_ClassDeclEntity.h
//

#ifndef LZZ_smtc_ClassDeclEntity_h
#define LZZ_smtc_ClassDeclEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_ClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassDeclEntity : public Entity
  {
    ClassDeclPtr m_class_decl;
  public:
    ClassDeclEntity (ClassDeclPtr const & class_decl);
    ~ ClassDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    ClassDeclPtr const & getClassDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ClassDeclEntity.inl"
#endif
#endif
