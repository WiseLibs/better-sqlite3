// smtc_ClassScope.h
//

#ifndef LZZ_smtc_ClassScope_h
#define LZZ_smtc_ClassScope_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_Scope.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassScope : public Scope
  {
    ClassDefnPtr m_class_defn;
  public:
    ClassScope (ClassDefnPtr const & class_defn);
    ~ ClassScope ();
    void accept (ScopeVisitor const & visitor) const;
    ClassDefnPtr const & getClassDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ClassScope.inl"
#endif
#endif
