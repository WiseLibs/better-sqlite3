// smtc_Type.h
//

#ifndef LZZ_smtc_Type_h
#define LZZ_smtc_Type_h
#include "smtc_TypeKind.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Type
  {
  public:
    Type ();
    virtual ~ Type ();
    virtual TypeKind getKind () const = 0;
    virtual util::String toString (util::String const & dcl, bool c, bool v) const = 0;
  };
}
#undef LZZ_INLINE
#endif
