// smtc_GetNameIfIdent.cpp
//

#include "smtc_GetNameIfIdent.h"
// semantic
#include "smtc_GetBaseNameIfIdent.h"
#include "smtc_NameVisitor.h"
#include "smtc_NonTmplName.h"
#include "smtc_TmplName.h"

#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct GetNameIfIdent : NameVisitor
  {
    util::Ident & ident;
    void visit (TmplName const & name) const;
    void visit (NonTmplName const & name) const;
  public:
    explicit GetNameIfIdent (util::Ident & ident);
    ~ GetNameIfIdent ();
  };
}
namespace
{
  void GetNameIfIdent::visit (TmplName const & name) const
    {
      ident = getBaseNameIfIdent (name.getBaseName ());
    }
}
namespace
{
  void GetNameIfIdent::visit (NonTmplName const & name) const
    {
      ident = getBaseNameIfIdent (name.getBaseName ());
    }
}
namespace
{
  LZZ_INLINE GetNameIfIdent::GetNameIfIdent (util::Ident & ident)
    : ident (ident)
         {}
}
namespace
{
  GetNameIfIdent::~ GetNameIfIdent ()
         {}
}
namespace smtc
{
  util::Ident getNameIfIdent (NamePtr const & name)
  {
    util::Ident ident;
    name->accept (GetNameIfIdent (ident));
    return ident;
  }
}
#undef LZZ_INLINE
