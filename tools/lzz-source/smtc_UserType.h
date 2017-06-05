// smtc_UserType.h
//

#ifndef LZZ_smtc_UserType_h
#define LZZ_smtc_UserType_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  class UserType : public Type
  {
    NamePtr m_name;
  public:
    UserType (NamePtr const & name);
    ~ UserType ();
    TypeKind getKind () const;
    util::String toString (util::String const & dcl, bool c, bool v) const;
    NamePtr const & getName () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_UserType.inl"
#endif
#endif
