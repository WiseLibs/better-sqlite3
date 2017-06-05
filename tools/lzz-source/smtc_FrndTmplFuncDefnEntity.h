// smtc_FrndTmplFuncDefnEntity.h
//

#ifndef LZZ_smtc_FrndTmplFuncDefnEntity_h
#define LZZ_smtc_FrndTmplFuncDefnEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_TmplFuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FrndTmplFuncDefnEntity : public Entity
  {
    TmplFuncDefnPtr m_tmpl_func_defn;
  public:
    FrndTmplFuncDefnEntity (TmplFuncDefnPtr const & tmpl_func_defn);
    ~ FrndTmplFuncDefnEntity ();
    void accept (EntityVisitor const & visitor) const;
    TmplFuncDefnPtr const & getTmplFuncDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FrndTmplFuncDefnEntity.inl"
#endif
#endif
