// smtc_ElabType.h
//

#ifndef LZZ_smtc_ElabType_h
#define LZZ_smtc_ElabType_h
// semantic
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ElabType : public Type
  {
    ClassKey m_key;
    NamePtr m_name;
  public:
    ElabType (ClassKey key, NamePtr const & name);
    ~ ElabType ();
    TypeKind getKind () const;
    util::String toString (util::String const & dcl, bool c, bool v) const;
  };
}
#undef LZZ_INLINE
#endif
