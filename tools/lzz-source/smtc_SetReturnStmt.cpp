// smtc_SetReturnStmt.cpp
//

#include "smtc_SetReturnStmt.h"
// semantic
#include "smtc_Message.h"
#include "smtc_NavClass.h"
#include "smtc_NavClassScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_VdfBlockDataScope.h"
#include "smtc_VdfDataFuncDefn.h"

#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct SetReturnStmt : ScopeVisitor
  {
    gram::Block const & stmt;
    void visit (NavClassScope const & scope) const;
    void visit (VdfBlockDataScope const & scope) const;
  public:
    explicit SetReturnStmt (gram::Block const & stmt);
    ~ SetReturnStmt ();
  };
}
namespace
{
  void SetReturnStmt::visit (NavClassScope const & scope) const
    {
      NavClassPtr const & nav_class = scope.getNavClass ();
      if (nav_class->hasReturnStmt ())
      {
        msg::navAlreadyHasReturn (stmt.getLoc ());
      }
      else
      {
        nav_class->setReturnStmt (stmt);
      }
    }
}
namespace
{
  void SetReturnStmt::visit (VdfBlockDataScope const & scope) const
    {
      VdfDataFuncDefnPtr const & func_defn = scope.getVdfDataFuncDefn ();
      func_defn->setReturnStmt (stmt);
    }
}
namespace
{
  LZZ_INLINE SetReturnStmt::SetReturnStmt (gram::Block const & stmt)
    : stmt (stmt)
         {}
}
namespace
{
  SetReturnStmt::~ SetReturnStmt ()
         {}
}
namespace smtc
{
  void setReturnStmt (ScopePtr const & cs, gram::Block const & stmt)
  {
    cs->accept (SetReturnStmt (stmt));
  }
}
#undef LZZ_INLINE
