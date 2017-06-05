// smtc_GetNameLoc.cpp
//

#include "smtc_GetNameLoc.h"
// semantic
#include "smtc_BaseName.h"
#include "smtc_BitfName.h"
#include "smtc_NameVisitor.h"
#include "smtc_NonTmplName.h"
#include "smtc_QualName.h"
#include "smtc_TmplName.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct GetNameLoc : NameVisitor
  {
    util::Loc & loc;
    void visit (QualName const & name) const;
    void visit (TmplName const & name) const;
    void visit (NonTmplName const & name) const;
    void visit (BitfName const & name) const;
  public:
    explicit GetNameLoc (util::Loc & loc);
    ~ GetNameLoc ();
  };
}
namespace
{
  void GetNameLoc::visit (QualName const & name) const
    {
      loc = getNameLoc (name.getUnqlName ());
    }
}
namespace
{
  void GetNameLoc::visit (TmplName const & name) const
    {
      loc = name.getBaseName ()->getLoc ();
    }
}
namespace
{
  void GetNameLoc::visit (NonTmplName const & name) const
    {
      loc = name.getBaseName ()->getLoc ();
    }
}
namespace
{
  void GetNameLoc::visit (BitfName const & name) const
    {
      loc = name.getLoc ();
    }
}
namespace
{
  LZZ_INLINE GetNameLoc::GetNameLoc (util::Loc & loc)
    : loc (loc)
         {}
}
namespace
{
  GetNameLoc::~ GetNameLoc ()
         {}
}
namespace smtc
{
  util::Loc getNameLoc (smtc::NamePtr const & name)
  {
    util::Loc loc;
    name->accept (GetNameLoc (loc));
    return loc;
  }
}
#undef LZZ_INLINE
