// smtc_OperBaseName.h
//

#ifndef LZZ_smtc_OperBaseName_h
#define LZZ_smtc_OperBaseName_h
#include "smtc_BaseName.h"
#include "smtc_OperKind.h"
#define LZZ_INLINE inline
namespace smtc
{
  class OperBaseName : public BaseName
  {
    OperKind m_kind;
  public:
    OperBaseName (util::Loc const & loc, util::Ident const & macro, OperKind kind);
    ~ OperBaseName ();
    void accept (BaseNameVisitor const & visitor) const;
    OperKind getOperKind () const;
  };
}
#undef LZZ_INLINE
#endif
