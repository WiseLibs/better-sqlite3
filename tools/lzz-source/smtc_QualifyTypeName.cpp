// smtc_QualifyTypeName.cpp
//

#include "smtc_QualifyTypeName.h"
// semantic
#include "smtc_CreateQualName.h"
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
  struct QualifyTypeName : NameVisitor
  {
    NamePtr const & name_ptr;
    util::IdentSet const & type_name_set;
    NamePtr const & qual_name;
    bool & result;
    NamePtr & res_name;
    void visit (TmplName const & name) const;
    void visit (NonTmplName const & name) const;
    void qualifyBaseName (BaseNamePtr const & base_name) const;
  public:
    explicit QualifyTypeName (NamePtr const & name_ptr, util::IdentSet const & type_name_set, NamePtr const & qual_name, bool & result, NamePtr & res_name);
    ~ QualifyTypeName ();
  };
}
namespace
{
  void QualifyTypeName::visit (TmplName const & name) const
    {
      qualifyBaseName (name.getBaseName ());
    }
}
namespace
{
  void QualifyTypeName::visit (NonTmplName const & name) const
    {
      qualifyBaseName (name.getBaseName ());
    }
}
namespace
{
  void QualifyTypeName::qualifyBaseName (BaseNamePtr const & base_name) const
    {
      util::Ident ident = getBaseNameIfIdent (base_name);
      if (ident.isSet ())
      {
        util::IdentSetConstIter i = type_name_set.find (ident);
        if (i != type_name_set.end ())
        {
          res_name = createQualName (qual_name, name_ptr);
          result = true;
        }
      }
    }
}
namespace
{
  LZZ_INLINE QualifyTypeName::QualifyTypeName (NamePtr const & name_ptr, util::IdentSet const & type_name_set, NamePtr const & qual_name, bool & result, NamePtr & res_name)
    : name_ptr (name_ptr), type_name_set (type_name_set), qual_name (qual_name), result (result), res_name (res_name)
         {}
}
namespace
{
  QualifyTypeName::~ QualifyTypeName ()
         {}
}
namespace smtc
{
  bool qualifyTypeName (NamePtr const & name, util::IdentSet const & type_name_set, NamePtr const & qual_name, NamePtr & res_name)
  {
    bool result = false;
    name->accept (QualifyTypeName (name, type_name_set, qual_name, result, res_name));
    return result;
  }
}
#undef LZZ_INLINE
