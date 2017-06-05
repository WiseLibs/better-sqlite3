// smtc_TmplFuncDefnEntity.h
//

#ifndef LZZ_smtc_TmplFuncDefnEntity_h
#define LZZ_smtc_TmplFuncDefnEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_TmplFuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplFuncDefnEntity : public Entity
  {
    TmplFuncDefnPtr m_tmpl_func_defn;
  public:
    TmplFuncDefnEntity (TmplFuncDefnPtr const & tmpl_func_defn);
    ~ TmplFuncDefnEntity ();
    void accept (EntityVisitor const & visitor) const;
    TmplFuncDefnPtr const & getTmplFuncDefn () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplFuncDefnEntity.inl"
#endif
#endif
