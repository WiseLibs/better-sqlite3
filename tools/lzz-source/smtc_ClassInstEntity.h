// smtc_ClassInstEntity.h
//

#ifndef LZZ_smtc_ClassInstEntity_h
#define LZZ_smtc_ClassInstEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_ClassDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassInstEntity : public Entity
  {
    ClassDeclPtr m_class_decl;
  public:
    ClassInstEntity (ClassDeclPtr const & class_decl);
    ~ ClassInstEntity ();
    void accept (EntityVisitor const & visitor) const;
    ClassDeclPtr const & getClassDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ClassInstEntity.inl"
#endif
#endif
