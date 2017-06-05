// smtc_DefineEnum.cpp
//

#include "smtc_DefineEnum.h"
// semantic
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateEnum.h"
#include "smtc_CreateEnumEntity.h"
#include "smtc_GetNameIfIdent.h"
#include "smtc_GetNameLoc.h"
#include "smtc_IsNameQual.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DefineEnum : ScopeVisitor
  {
    util::Loc const & loc;
    NamePtr const & name;
    EnumtorPtrVector const & enumtor_set;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void checkName () const;
    EntityPtr buildEntity () const;
  public:
    explicit DefineEnum (util::Loc const & loc, NamePtr const & name, EnumtorPtrVector const & enumtor_set);
    ~ DefineEnum ();
  };
}
namespace
{
  void DefineEnum::visit (NsScope const & scope) const
    {
      // check name
      checkName ();

      // add entity to ns
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DefineEnum::visit (ClassScope const & scope) const
    {
      // check name
      checkName ();

      // store type name in scope
      ClassDefnPtr const & class_defn = scope.getClassDefn ();
      if (name.isSet ())
      {
        util::Ident ident = getNameIfIdent (name);
        if (ident.isSet ())
        {
          class_defn->addTypeName (ident);
        }
      }

      // add entity to class
      class_defn->addEntity (buildEntity ());
    }
}
namespace
{
  void DefineEnum::checkName () const
    {
      // cannot be qualified
      if (name.isSet () && isNameQual (name))
      {
        msg::qualEnumDefn (getNameLoc (name));
      }
    }
}
namespace
{
  EntityPtr DefineEnum::buildEntity () const
    {
      EnumPtr en = createEnum (loc, name, enumtor_set);
      return createEnumEntity (en);
    }
}
namespace
{
  LZZ_INLINE DefineEnum::DefineEnum (util::Loc const & loc, NamePtr const & name, EnumtorPtrVector const & enumtor_set)
    : loc (loc), name (name), enumtor_set (enumtor_set)
         {}
}
namespace
{
  DefineEnum::~ DefineEnum ()
         {}
}
namespace smtc
{
  void defineEnum (ScopePtr const & scope, util::Loc const & loc, NamePtr const & name, EnumtorPtrVector const & enumtor_set)
  {
    scope->accept (DefineEnum (loc, name, enumtor_set));
  }
}
#undef LZZ_INLINE
