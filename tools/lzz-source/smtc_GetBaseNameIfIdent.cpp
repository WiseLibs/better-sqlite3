// smtc_GetBaseNameIfIdent.cpp
//

#include "smtc_GetBaseNameIfIdent.h"
// semantic
#include "smtc_BaseNameVisitor.h"
#include "smtc_IdentBaseName.h"

#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct GetBaseNameIfIdent : BaseNameVisitor
  {
    util::Ident & ident;
    void visit (IdentBaseName const & base_name) const;
  public:
    explicit GetBaseNameIfIdent (util::Ident & ident);
    ~ GetBaseNameIfIdent ();
  };
}
namespace
{
  void GetBaseNameIfIdent::visit (IdentBaseName const & base_name) const
    {
      ident = base_name.getIdent ();
    }
}
namespace
{
  LZZ_INLINE GetBaseNameIfIdent::GetBaseNameIfIdent (util::Ident & ident)
    : ident (ident)
         {}
}
namespace
{
  GetBaseNameIfIdent::~ GetBaseNameIfIdent ()
         {}
}
namespace smtc
{
  util::Ident getBaseNameIfIdent (BaseNamePtr const & base_name)
  {
    util::Ident ident;
    base_name->accept (GetBaseNameIfIdent (ident));
    return ident;
  }
}
#undef LZZ_INLINE
