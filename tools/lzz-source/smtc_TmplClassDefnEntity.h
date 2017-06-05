// smtc_TmplClassDefnEntity.h
//

#ifndef LZZ_smtc_TmplClassDefnEntity_h
#define LZZ_smtc_TmplClassDefnEntity_h
// semantic
#include "smtc_TmplClassDeclEntity.h"
#include "smtc_TmplClassDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplClassDefnEntity : public TmplClassDeclEntity
  {
  public:
    TmplClassDefnEntity (TmplClassDefnPtr const & tmpl_class_defn);
    ~ TmplClassDefnEntity ();
    void accept (EntityVisitor const & visitor) const;
    TmplClassDefnPtr getTmplClassDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplClassDefnEntity.inl"
#endif
#endif
