// smtc_PrintMbrDecl.cpp
//

#include "smtc_PrintMbrDecl.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_AcceptEntityVisitor.h"
#include "smtc_ClassDefn.h"
#include "smtc_EntityVisitor.h"
#include "smtc_PrintAccessSpec.h"
#include "smtc_PrintMbrClassDecl.h"
#include "smtc_PrintMbrClassDefn.h"
#include "smtc_PrintMbrEnum.h"
#include "smtc_PrintMbrFrndClassDecl.h"
#include "smtc_PrintMbrFrndFuncDecl.h"
#include "smtc_PrintMbrFrndFuncDefn.h"
#include "smtc_PrintMbrFrndFuncDefn.h"
#include "smtc_PrintMbrFrndTmplClassDecl.h"
#include "smtc_PrintMbrFrndTmplFuncDecl.h"
#include "smtc_PrintMbrFrndTmplFuncDefn.h"
#include "smtc_PrintMbrFuncDecl.h"
#include "smtc_PrintMbrLazyClass.h"
#include "smtc_PrintMbrObjDecl.h"
#include "smtc_PrintMbrTdef.h"
#include "smtc_PrintMbrTmplClassDecl.h"
#include "smtc_PrintMbrTmplClassDefn.h"
#include "smtc_PrintMbrTmplFuncDecl.h"
#include "smtc_PrintMbrTmplLazyClass.h"
#include "smtc_PrintMbrUsingDecl.h"

// entities
#include "smtc_AccessSpecEntity.h"
#include "smtc_ClassDeclEntity.h"
#include "smtc_ClassDefnEntity.h"
#include "smtc_EnumEntity.h"
#include "smtc_FrndClassDeclEntity.h"
#include "smtc_FrndFuncDeclEntity.h"
#include "smtc_FrndFuncDefnEntity.h"
#include "smtc_FrndTmplClassDeclEntity.h"
#include "smtc_FrndTmplFuncDeclEntity.h"
#include "smtc_FrndTmplFuncDefnEntity.h"
#include "smtc_FuncDeclEntity.h"
#include "smtc_FuncDefnEntity.h"
#include "smtc_LazyClassEntity.h"
#include "smtc_ObjEntity.h"
#include "smtc_TdefEntity.h"
#include "smtc_TmplClassDeclEntity.h"
#include "smtc_TmplClassDefnEntity.h"
#include "smtc_TmplFuncDeclEntity.h"
#include "smtc_TmplFuncDefnEntity.h"
#include "smtc_TmplLazyClassEntity.h"
#include "smtc_UsingDeclEntity.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct PrintMbrDecl : EntityVisitor
  {
    FilePtr const & file;
    void visit (AccessSpecEntity const & entity) const;
    void visit (TdefEntity const & entity) const;
    void visit (ObjEntity const & entity) const;
    void visit (FuncDeclEntity const & entity) const;
    void visit (FrndFuncDeclEntity const & entity) const;
    void visit (FuncDefnEntity const & entity) const;
    void visit (FrndFuncDefnEntity const & entity) const;
    void visit (TmplFuncDeclEntity const & entity) const;
    void visit (TmplFuncDefnEntity const & entity) const;
    void visit (FrndTmplFuncDeclEntity const & entity) const;
    void visit (FrndTmplFuncDefnEntity const & entity) const;
    void visit (ClassDeclEntity const & entity) const;
    void visit (TmplClassDeclEntity const & entity) const;
    void visit (FrndClassDeclEntity const & entity) const;
    void visit (FrndTmplClassDeclEntity const & entity) const;
    void visit (ClassDefnEntity const & entity) const;
    void visit (TmplClassDefnEntity const & entity) const;
    void visit (LazyClassEntity const & entity) const;
    void visit (TmplLazyClassEntity const & entity) const;
    void visit (EnumEntity const & entity) const;
    void visit (UsingDeclEntity const & entity) const;
  public:
    explicit PrintMbrDecl (FilePtr const & file);
    ~ PrintMbrDecl ();
  };
}
namespace
{
  void PrintMbrDecl::visit (AccessSpecEntity const & entity) const
    {
      printAccessSpec (file, entity.getAccessSpec ());
    }
}
namespace
{
  void PrintMbrDecl::visit (TdefEntity const & entity) const
    {
      printMbrTdef (file, entity.getTdef ());
    }
}
namespace
{
  void PrintMbrDecl::visit (ObjEntity const & entity) const
    {
      printMbrObjDecl (file, entity.getObj ());
    }
}
namespace
{
  void PrintMbrDecl::visit (FuncDeclEntity const & entity) const
    {
      printMbrFuncDecl (file, entity.getFuncDecl ());
    }
}
namespace
{
  void PrintMbrDecl::visit (FrndFuncDeclEntity const & entity) const
    {
      printMbrFrndFuncDecl (file, entity.getFuncDecl ());
    }
}
namespace
{
  void PrintMbrDecl::visit (FuncDefnEntity const & entity) const
    {
      printMbrFuncDecl (file, entity.getFuncDefn ());
    }
}
namespace
{
  void PrintMbrDecl::visit (FrndFuncDefnEntity const & entity) const
    {
      printMbrFrndFuncDefn (file, entity.getFuncDefn ());
    }
}
namespace
{
  void PrintMbrDecl::visit (TmplFuncDeclEntity const & entity) const
    {
      printMbrTmplFuncDecl (file, entity.getTmplFuncDecl ());
    }
}
namespace
{
  void PrintMbrDecl::visit (TmplFuncDefnEntity const & entity) const
    {
      printMbrTmplFuncDecl (file, entity.getTmplFuncDefn ());
    }
}
namespace
{
  void PrintMbrDecl::visit (FrndTmplFuncDeclEntity const & entity) const
    {
      printMbrFrndTmplFuncDecl (file, entity.getTmplFuncDecl ());
    }
}
namespace
{
  void PrintMbrDecl::visit (FrndTmplFuncDefnEntity const & entity) const
    {
      printMbrFrndTmplFuncDefn (file, entity.getTmplFuncDefn ());
    }
}
namespace
{
  void PrintMbrDecl::visit (ClassDeclEntity const & entity) const
    {
      printMbrClassDecl (file, entity.getClassDecl ());
    }
}
namespace
{
  void PrintMbrDecl::visit (TmplClassDeclEntity const & entity) const
    {
      printMbrTmplClassDecl (file, entity.getTmplClassDecl ());
    }
}
namespace
{
  void PrintMbrDecl::visit (FrndClassDeclEntity const & entity) const
    {
      printMbrFrndClassDecl (file, entity.getClassDecl ());
    }
}
namespace
{
  void PrintMbrDecl::visit (FrndTmplClassDeclEntity const & entity) const
    {
      printMbrFrndTmplClassDecl (file, entity.getTmplClassDecl ());
    }
}
namespace
{
  void PrintMbrDecl::visit (ClassDefnEntity const & entity) const
    {
      printMbrClassDefn (file, entity.getClassDefn ());
    }
}
namespace
{
  void PrintMbrDecl::visit (TmplClassDefnEntity const & entity) const
    {
      printMbrTmplClassDefn (file, entity.getTmplClassDefn ());
    }
}
namespace
{
  void PrintMbrDecl::visit (LazyClassEntity const & entity) const
    {
      printMbrLazyClass (file, entity.getLazyClass ());
    }
}
namespace
{
  void PrintMbrDecl::visit (TmplLazyClassEntity const & entity) const
    {
      printMbrTmplLazyClass (file, entity.getTmplLazyClass ());
    }
}
namespace
{
  void PrintMbrDecl::visit (EnumEntity const & entity) const
    {
      printMbrEnum (file, entity.getEnum ());
    }
}
namespace
{
  void PrintMbrDecl::visit (UsingDeclEntity const & entity) const
    {
      printMbrUsingDecl (file, entity.getUsingDecl ());
    }
}
namespace
{
  LZZ_INLINE PrintMbrDecl::PrintMbrDecl (FilePtr const & file)
    : file (file)
         {}
}
namespace
{
  PrintMbrDecl::~ PrintMbrDecl ()
         {}
}
namespace smtc
{
  void printMbrDecl (FilePtr const & file, ClassDefnPtr const & class_defn)
  {
    EntityPtrDeque const & entity_set = class_defn->getEntitySet ();
    std::for_each (entity_set.begin (), entity_set.end (), AcceptEntityVisitor (PrintMbrDecl (file)));
  }
}
#undef LZZ_INLINE
