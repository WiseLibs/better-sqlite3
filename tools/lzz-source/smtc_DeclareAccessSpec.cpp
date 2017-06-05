// smtc_DeclareAccessSpec.cpp
//

#include "smtc_DeclareAccessSpec.h"
// semantic
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateAccessSpec.h"
#include "smtc_CreateAccessSpecEntity.h"
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DeclareAccessSpec : ScopeVisitor
  {
    util::Loc const & loc;
    Access access;
    void visit (ClassScope const & scope) const;
  public:
    explicit DeclareAccessSpec (util::Loc const & loc, Access access);
    ~ DeclareAccessSpec ();
  };
}
namespace
{
  void DeclareAccessSpec::visit (ClassScope const & scope) const
    {
      // create acces spec and add to class
      AccessSpecPtr access_spec = createAccessSpec (loc, access);
      scope.getClassDefn ()->addEntity (createAccessSpecEntity (access_spec));
    }
}
namespace
{
  LZZ_INLINE DeclareAccessSpec::DeclareAccessSpec (util::Loc const & loc, Access access)
    : loc (loc), access (access)
         {}
}
namespace
{
  DeclareAccessSpec::~ DeclareAccessSpec ()
         {}
}
namespace smtc
{
  void declareAccessSpec (ScopePtr const & scope, util::Loc const & loc, Access access)
  {
    scope->accept (DeclareAccessSpec (loc, access));
  }
}
#undef LZZ_INLINE
