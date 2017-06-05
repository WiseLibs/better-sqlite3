// smtc_ClassDefnEntity.h
//

#ifndef LZZ_smtc_ClassDefnEntity_h
#define LZZ_smtc_ClassDefnEntity_h
// semantic
#include "smtc_ClassDeclEntity.h"
#include "smtc_ClassDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassDefnEntity : public ClassDeclEntity
  {
  public:
    ClassDefnEntity (ClassDefnPtr const & class_defn);
    ~ ClassDefnEntity ();
    void accept (EntityVisitor const & visitor) const;
    ClassDefnPtr getClassDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ClassDefnEntity.inl"
#endif
#endif
