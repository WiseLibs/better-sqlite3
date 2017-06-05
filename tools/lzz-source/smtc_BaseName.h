// smtc_BaseName.h
//

#ifndef LZZ_smtc_BaseName_h
#define LZZ_smtc_BaseName_h
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  class BaseNameVisitor;
}
namespace smtc
{
  class BaseName
  {
    util::Loc m_loc;
    util::Ident m_macro;
  public:
    BaseName (util::Loc const & loc, util::Ident const & macro);
    virtual ~ BaseName ();
    util::Loc const & getLoc () const;
    bool hasMacro () const;
    util::Ident const & getMacro () const;
    virtual void accept (BaseNameVisitor const & visitor) const = 0;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_BaseName.inl"
#endif
#endif
