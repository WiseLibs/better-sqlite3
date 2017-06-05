// smtc_FormTmplName.cpp
//

#include "smtc_FormTmplName.h"
// std lib
#include <cassert>

// semantic
#include "smtc_CreateQualName.h"
#include "smtc_CreateTmplName.h"
#include "smtc_NameVisitor.h"
#include "smtc_NonTmplName.h"
#include "smtc_QualName.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct FormTmplName : NameVisitor
  {
    util::String const & args;
    NamePtr & result;
    void visit (QualName const & name) const;
    void visit (NonTmplName const & name) const;
  public:
    explicit FormTmplName (util::String const & args, NamePtr & result);
    ~ FormTmplName ();
  };
}
namespace
{
  void FormTmplName::visit (QualName const & name) const
    {
      result = createQualName (name.getQualName (), formTmplName (name.getUnqlName (), args));
    }
}
namespace
{
  void FormTmplName::visit (NonTmplName const & name) const
    {
      result = createTmplName (name.getBaseName (), false, args);
    }
}
namespace
{
  LZZ_INLINE FormTmplName::FormTmplName (util::String const & args, NamePtr & result)
    : args (args), result (result)
         {}
}
namespace
{
  FormTmplName::~ FormTmplName ()
         {}
}
namespace smtc
{
  NamePtr formTmplName (NamePtr const & name, util::String const & args)
  {
    NamePtr result = name;
    name->accept (FormTmplName (args, result));
    return result;
  }
}
#undef LZZ_INLINE
