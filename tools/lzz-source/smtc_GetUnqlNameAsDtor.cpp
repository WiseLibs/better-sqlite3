// smtc_GetUnqlNameAsDtor.cpp
//

#include "smtc_GetUnqlNameAsDtor.h"
// semantic
#include "smtc_BaseNameVisitor.h"
#include "smtc_CreateDtorBaseName.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateTmplName.h"
#include "smtc_IdentBaseName.h"
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
  struct GetBaseNameAsDtor : BaseNameVisitor
  {
    BaseNamePtr & res_base_name;
    void visit (IdentBaseName const & base_name) const;
  public:
    explicit GetBaseNameAsDtor (BaseNamePtr & res_base_name);
    ~ GetBaseNameAsDtor ();
  };
}
namespace
{
  BaseNamePtr getBaseNameAsDtor (BaseNamePtr const & base_name);
}
namespace
{
  struct GetUnqlNameAsDtor : NameVisitor
  {
    NamePtr & res_name;
    void visit (TmplName const & name) const;
    void visit (NonTmplName const & name) const;
  public:
    explicit GetUnqlNameAsDtor (NamePtr & res_name);
    ~ GetUnqlNameAsDtor ();
  };
}
namespace
{
  void GetBaseNameAsDtor::visit (IdentBaseName const & base_name) const
    {
      res_base_name = createDtorBaseName (base_name.getLoc (), base_name.getIdent ());
    }
}
namespace
{
  LZZ_INLINE GetBaseNameAsDtor::GetBaseNameAsDtor (BaseNamePtr & res_base_name)
    : res_base_name (res_base_name)
         {}
}
namespace
{
  GetBaseNameAsDtor::~ GetBaseNameAsDtor ()
         {}
}
namespace
{
  BaseNamePtr getBaseNameAsDtor (BaseNamePtr const & base_name)
  {
    BaseNamePtr res_base_name = base_name;
    base_name->accept (GetBaseNameAsDtor (res_base_name));
    return res_base_name;
  }
}
namespace
{
  void GetUnqlNameAsDtor::visit (TmplName const & name) const
    {
      res_name = createTmplName (getBaseNameAsDtor (name.getBaseName ()), name.hasTemplateKeyword (), name.getArgs ());
    }
}
namespace
{
  void GetUnqlNameAsDtor::visit (NonTmplName const & name) const
    {
      res_name = createNonTmplName (getBaseNameAsDtor (name.getBaseName ()));
    }
}
namespace
{
  LZZ_INLINE GetUnqlNameAsDtor::GetUnqlNameAsDtor (NamePtr & res_name)
    : res_name (res_name)
         {}
}
namespace
{
  GetUnqlNameAsDtor::~ GetUnqlNameAsDtor ()
         {}
}
namespace smtc
{
  NamePtr getUnqlNameAsDtor (NamePtr const & name)
  {
    NamePtr res_name = name;
    name->accept (GetUnqlNameAsDtor (res_name));
    return res_name;
  }
}
#undef LZZ_INLINE
