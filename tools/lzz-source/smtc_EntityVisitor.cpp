// smtc_EntityVisitor.cpp
//

#include "smtc_EntityVisitor.h"
// semantic
#include "smtc_LazyClassEntity.h"
#include "smtc_NavClassEntity.h"
#include "smtc_NavSubmitFuncDefnEntity.h"
#include "smtc_TmplLazyClassEntity.h"
#include "smtc_VdfClassEntity.h"
#include "smtc_VdfDataFuncDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  void EntityVisitor::visit (NsEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (ObjEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FuncDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (ClassDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (ClassDefnEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FuncDefnEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FrndClassDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (TdefEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FrndFuncDefnEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FrndFuncDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (TmplClassDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FrndTmplClassDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (TmplClassDefnEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (TmplFuncDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (TmplFuncDefnEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FrndTmplFuncDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FrndTmplFuncDefnEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (AccessSpecEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (ClassInstEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (FuncInstEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (LazyClassEntity const & entity) const
    {
      visit (static_cast <ClassDefnEntity const &> (entity));
    }
}
namespace smtc
{
  void EntityVisitor::visit (TmplLazyClassEntity const & entity) const
    {
      visit (static_cast <TmplClassDefnEntity const &> (entity));
    }
}
namespace smtc
{
  void EntityVisitor::visit (EnumEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (UsingDeclEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (UsingDirEntity const & entity) const
    {}
}
namespace smtc
{
  void EntityVisitor::visit (NavClassEntity const & entity) const
    {
      visit (static_cast <ClassDefnEntity const &> (entity));
    }
}
namespace smtc
{
  void EntityVisitor::visit (NavSubmitFuncDefnEntity const & entity) const
    {
      visit (static_cast <FuncDeclEntity const &> (entity));
    }
}
namespace smtc
{
  void EntityVisitor::visit (VdfClassEntity const & entity) const
    {
      visit (static_cast <ClassDefnEntity const &> (entity));
    }
}
namespace smtc
{
  void EntityVisitor::visit (VdfDataFuncDefnEntity const & entity) const
    {
      visit (static_cast <FuncDeclEntity const &> (entity));
    }
}
#undef LZZ_INLINE
