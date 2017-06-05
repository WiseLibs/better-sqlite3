// smtc_GetUnqlNamePart.cpp
//

#include "smtc_GetUnqlNamePart.h"
// semantic
#include "smtc_CreateTmplName.h"
#include "smtc_NameVisitor.h"
#include "smtc_QualName.h"
#include "smtc_TmplName.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct GetUnqlNamePart : NameVisitor
  {
    NamePtr & res_name;
    void visit (QualName const & name) const;
    void visit (TmplName const & name) const;
  public:
    explicit GetUnqlNamePart (NamePtr & res_name);
    ~ GetUnqlNamePart ();
  };
}
namespace
{
  void GetUnqlNamePart::visit (QualName const & name) const
    {
      res_name = getUnqlNamePart (name.getUnqlName ());
    }
}
namespace
{
  void GetUnqlNamePart::visit (TmplName const & name) const
    {
      // remove template keyword if used
      if (name.hasTemplateKeyword ())
      {
        res_name = createTmplName (name.getBaseName (), false, name.getArgs ());
      }
    }
}
namespace
{
  LZZ_INLINE GetUnqlNamePart::GetUnqlNamePart (NamePtr & res_name)
    : res_name (res_name)
         {}
}
namespace
{
  GetUnqlNamePart::~ GetUnqlNamePart ()
         {}
}
namespace smtc
{
  NamePtr getUnqlNamePart (NamePtr const & name)
  {
    NamePtr res_name = name;
    name->accept (GetUnqlNamePart (res_name));
    return res_name;
  }
}
#undef LZZ_INLINE
