// smtc_ParamDecl.h
//

#ifndef LZZ_smtc_ParamDecl_h
#define LZZ_smtc_ParamDecl_h
// navg
#include "smtc_NamePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ParamDecl
  {
    NamePtr m_name;
  public:
    ParamDecl (NamePtr const & name);
    virtual ~ ParamDecl ();
    NamePtr const & getName () const;
    virtual util::String toString (bool is_decl) const = 0;
  };
}
#undef LZZ_INLINE
#endif
