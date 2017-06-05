// smtc_DtorBaseName.h
//

#ifndef LZZ_smtc_DtorBaseName_h
#define LZZ_smtc_DtorBaseName_h
#include "smtc_BaseName.h"
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  class DtorBaseName : public BaseName
  {
    util::Ident m_ident;
  public:
    DtorBaseName (util::Loc const & loc, util::Ident const & macro, util::Ident const & ident);
    ~ DtorBaseName ();
    void accept (BaseNameVisitor const & visitor) const;
    util::Ident const & getIdent () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_DtorBaseName.inl"
#endif
#endif
