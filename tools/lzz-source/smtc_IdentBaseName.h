// smtc_IdentBaseName.h
//

#ifndef LZZ_smtc_IdentBaseName_h
#define LZZ_smtc_IdentBaseName_h
#include "smtc_BaseName.h"
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  class IdentBaseName : public BaseName
  {
    util::Ident m_ident;
  public:
    IdentBaseName (util::Loc const & loc, util::Ident const & macro, util::Ident const & ident);
    ~ IdentBaseName ();
    void accept (BaseNameVisitor const & visitor) const;
    util::Ident const & getIdent () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_IdentBaseName.inl"
#endif
#endif
