// smtc_DeclareUsingDir.cpp
//

#include "smtc_DeclareUsingDir.h"
// semantic
#include "smtc_CreateUsingDir.h"
#include "smtc_CreateUsingDirEntity.h"
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
  struct DeclareUsingDir : ScopeVisitor
  {
    NamePtr const & name;
    void visit (NsScope const & scope) const;
    EntityPtr buildEntity () const;
  public:
    explicit DeclareUsingDir (NamePtr const & name);
    ~ DeclareUsingDir ();
  };
}
namespace
{
  void DeclareUsingDir::visit (NsScope const & scope) const
    {
      // add entity to ns
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  EntityPtr DeclareUsingDir::buildEntity () const
    {
      UsingDirPtr using_dir = createUsingDir (name);
      return createUsingDirEntity (using_dir);
    }
}
namespace
{
  LZZ_INLINE DeclareUsingDir::DeclareUsingDir (NamePtr const & name)
    : name (name)
         {}
}
namespace
{
  DeclareUsingDir::~ DeclareUsingDir ()
         {}
}
namespace smtc
{
  void declareUsingDir (ScopePtr const & scope, NamePtr const & name)
  {
    scope->accept (DeclareUsingDir (name));
  }
}
#undef LZZ_INLINE
