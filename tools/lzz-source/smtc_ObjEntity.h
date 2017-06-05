// smtc_ObjEntity.h
//

#ifndef LZZ_smtc_ObjEntity_h
#define LZZ_smtc_ObjEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_ObjPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ObjEntity : public Entity
  {
    ObjPtr m_obj;
  public:
    ObjEntity (ObjPtr const & obj);
    ~ ObjEntity ();
    void accept (EntityVisitor const & visitor) const;
    ObjPtr const & getObj () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ObjEntity.inl"
#endif
#endif
