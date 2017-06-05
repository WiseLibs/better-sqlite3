// smtc_PrintNs.cpp
//

#include "smtc_PrintNs.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_AcceptEntityVisitor.h"
#include "smtc_EntityVisitor.h"
#include "smtc_Ns.h"
#include "smtc_PrintNsClassDecl.h"
#include "smtc_PrintNsClassDefn.h"
#include "smtc_PrintNsClassInst.h"
#include "smtc_PrintNsEnum.h"
#include "smtc_PrintNsFuncDecl.h"
#include "smtc_PrintNsFuncDefn.h"
#include "smtc_PrintNsFuncInst.h"
#include "smtc_PrintNsLazyClass.h"
#include "smtc_PrintNsNavClass.h"
#include "smtc_PrintNsObjDefn.h"
#include "smtc_PrintNsTdef.h"
#include "smtc_PrintNsTmplClassDecl.h"
#include "smtc_PrintNsTmplClassDefn.h"
#include "smtc_PrintNsTmplFuncDecl.h"
#include "smtc_PrintNsTmplFuncDefn.h"
#include "smtc_PrintNsTmplLazyClass.h"
#include "smtc_PrintNsUsingDecl.h"
#include "smtc_PrintNsUsingDir.h"
#include "smtc_PrintNsVdfClass.h"
#include "smtc_PrintNsVdfDataFuncDefn.h"

// entities
#include "smtc_ClassDeclEntity.h"
#include "smtc_ClassDefnEntity.h"
#include "smtc_ClassInstEntity.h"
#include "smtc_EnumEntity.h"
#include "smtc_FuncDeclEntity.h"
#include "smtc_FuncDefnEntity.h"
#include "smtc_FuncInstEntity.h"
#include "smtc_LazyClassEntity.h"
#include "smtc_NavClassEntity.h"
#include "smtc_NsEntity.h"
#include "smtc_ObjEntity.h"
#include "smtc_TdefEntity.h"
#include "smtc_TmplClassDeclEntity.h"
#include "smtc_TmplClassDefnEntity.h"
#include "smtc_TmplFuncDeclEntity.h"
#include "smtc_TmplFuncDefnEntity.h"
#include "smtc_TmplLazyClassEntity.h"
#include "smtc_UsingDeclEntity.h"
#include "smtc_UsingDirEntity.h"
#include "smtc_VdfClassEntity.h"
#include "smtc_VdfDataFuncDefnEntity.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct PrintNs : EntityVisitor
  {
    Output & out;
    NsPtr const & ns;
    void visit (NsEntity const & entity) const;
    void visit (TdefEntity const & entity) const;
    void visit (ObjEntity const & entity) const;
    void visit (FuncDeclEntity const & entity) const;
    void visit (TmplFuncDeclEntity const & entity) const;
    void visit (TmplFuncDefnEntity const & entity) const;
    void visit (FuncDefnEntity const & entity) const;
    void visit (ClassDeclEntity const & entity) const;
    void visit (TmplClassDeclEntity const & entity) const;
    void visit (ClassDefnEntity const & entity) const;
    void visit (TmplClassDefnEntity const & entity) const;
    void visit (ClassInstEntity const & entity) const;
    void visit (FuncInstEntity const & entity) const;
    void visit (LazyClassEntity const & entity) const;
    void visit (TmplLazyClassEntity const & entity) const;
    void visit (EnumEntity const & entity) const;
    void visit (UsingDeclEntity const & entity) const;
    void visit (UsingDirEntity const & entity) const;
    void visit (NavClassEntity const & entity) const;
    void visit (VdfClassEntity const & entity) const;
    void visit (VdfDataFuncDefnEntity const & entity) const;
  public:
    explicit PrintNs (Output & out, NsPtr const & ns);
    ~ PrintNs ();
  };
}
namespace
{
  void PrintNs::visit (NsEntity const & entity) const
    {
      printNs (out, entity.getNs ());
    }
}
namespace
{
  void PrintNs::visit (TdefEntity const & entity) const
    {
      printNsTdef (out, entity.getTdef (), ns);
    }
}
namespace
{
  void PrintNs::visit (ObjEntity const & entity) const
    {
      printNsObjDefn (out, entity.getObj (), ns);
    }
}
namespace
{
  void PrintNs::visit (FuncDeclEntity const & entity) const
    {
      printNsFuncDecl (out, entity.getFuncDecl (), ns);
    }
}
namespace
{
  void PrintNs::visit (TmplFuncDeclEntity const & entity) const
    {
      printNsTmplFuncDecl (out, entity.getTmplFuncDecl (), ns);
    }
}
namespace
{
  void PrintNs::visit (TmplFuncDefnEntity const & entity) const
    {
      printNsTmplFuncDefn (out, entity.getTmplFuncDefn (), ns);
    }
}
namespace
{
  void PrintNs::visit (FuncDefnEntity const & entity) const
    {
      printNsFuncDefn (out, entity.getFuncDefn (), ns);
    }
}
namespace
{
  void PrintNs::visit (ClassDeclEntity const & entity) const
    {
      printNsClassDecl (out, entity.getClassDecl (), ns);
    }
}
namespace
{
  void PrintNs::visit (TmplClassDeclEntity const & entity) const
    {
      printNsTmplClassDecl (out, entity.getTmplClassDecl (), ns);
    }
}
namespace
{
  void PrintNs::visit (ClassDefnEntity const & entity) const
    {
      printNsClassDefn (out, entity.getClassDefn (), ns);
    }
}
namespace
{
  void PrintNs::visit (TmplClassDefnEntity const & entity) const
    {
      printNsTmplClassDefn (out, entity.getTmplClassDefn (), ns);
    }
}
namespace
{
  void PrintNs::visit (ClassInstEntity const & entity) const
    {
      printNsClassInst (out, entity.getClassDecl (), ns);
    }
}
namespace
{
  void PrintNs::visit (FuncInstEntity const & entity) const
    {
      printNsFuncInst (out, entity.getFuncDecl (), ns);
    }
}
namespace
{
  void PrintNs::visit (LazyClassEntity const & entity) const
    {
      printNsLazyClass (out, entity.getLazyClass (), ns);
    }
}
namespace
{
  void PrintNs::visit (TmplLazyClassEntity const & entity) const
    {
      printNsTmplLazyClass (out, entity.getTmplLazyClass (), ns);
    }
}
namespace
{
  void PrintNs::visit (EnumEntity const & entity) const
    {
      printNsEnum (out, entity.getEnum (), ns);
    }
}
namespace
{
  void PrintNs::visit (UsingDeclEntity const & entity) const
    {
      printNsUsingDecl (out, entity.getUsingDecl (), ns);
    }
}
namespace
{
  void PrintNs::visit (UsingDirEntity const & entity) const
    {
      printNsUsingDir (out, entity.getUsingDir (), ns);
    }
}
namespace
{
  void PrintNs::visit (NavClassEntity const & entity) const
    {
      printNsNavClass (out, entity.getNavClass (), ns);
    }
}
namespace
{
  void PrintNs::visit (VdfClassEntity const & entity) const
    {
      printNsVdfClass (out, entity.getClassDefn (), ns);
    }
}
namespace
{
  void PrintNs::visit (VdfDataFuncDefnEntity const & entity) const
    {
      printNsVdfDataFuncDefn (out, entity.getVdfDataFuncDefn (), ns);
    }
}
namespace
{
  LZZ_INLINE PrintNs::PrintNs (Output & out, NsPtr const & ns)
    : out (out), ns (ns)
         {}
}
namespace
{
  PrintNs::~ PrintNs ()
         {}
}
namespace smtc
{
  void printNs (Output & out, NsPtr const & ns)
  {
    EntityPtrDeque const & entity_set = ns->getEntitySet ();
    std::for_each (entity_set.begin (), entity_set.end (), AcceptEntityVisitor (PrintNs (out, ns)));
  }
}
#undef LZZ_INLINE
