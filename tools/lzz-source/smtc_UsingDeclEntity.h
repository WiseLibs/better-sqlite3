// smtc_UsingDeclEntity.h
//

#ifndef LZZ_smtc_UsingDeclEntity_h
#define LZZ_smtc_UsingDeclEntity_h
// semantic
#include "smtc_Entity.h"
#include "smtc_UsingDeclPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UsingDeclEntity : public Entity
  {
    UsingDeclPtr m_using_decl;
  public:
    UsingDeclEntity (UsingDeclPtr const & using_decl);
    ~ UsingDeclEntity ();
    void accept (EntityVisitor const & visitor) const;
    UsingDeclPtr const & getUsingDecl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_UsingDeclEntity.inl"
#endif
#endif
