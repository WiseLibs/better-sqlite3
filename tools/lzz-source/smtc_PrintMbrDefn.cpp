// smtc_PrintMbrDefn.cpp
//

#include "smtc_PrintMbrDefn.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_AcceptEntityVisitor.h"
#include "smtc_ClassDefn.h"
#include "smtc_CreateQualName.h"
#include "smtc_EntityVisitor.h"
#include "smtc_PrintMbrFuncDefn.h"
#include "smtc_PrintNavSubmitFuncDefn.h"
#include "smtc_PrintMbrObjDefn.h"
#include "smtc_PrintMbrTmplFuncDefn.h"
#include "smtc_PrintTmplMbrDefn.h"

// entities
#include "smtc_ClassDefnEntity.h"
#include "smtc_FuncDefnEntity.h"
#include "smtc_NavSubmitFuncDefnEntity.h"
#include "smtc_ObjEntity.h"
#include "smtc_TmplClassDefnEntity.h"
#include "smtc_TmplFuncDefnEntity.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct PrintMbrDefn : EntityVisitor
  {
    Output & out;
    NsPtr const & ns;
    NamePtr const & qual_name;
    void visit (ObjEntity const & entity) const;
    void visit (FuncDefnEntity const & entity) const;
    void visit (TmplFuncDefnEntity const & entity) const;
    void visit (ClassDefnEntity const & entity) const;
    void visit (TmplClassDefnEntity const & entity) const;
    static void visitEntitySet (EntityPtrDeque const & entity_set, Output & out, NsPtr const & ns, NamePtr const & qual_name);
    void visit (NavSubmitFuncDefnEntity const & entity) const;
  public:
    explicit PrintMbrDefn (Output & out, NsPtr const & ns, NamePtr const & qual_name);
    ~ PrintMbrDefn ();
  };
}
namespace
{
  void PrintMbrDefn::visit (ObjEntity const & entity) const
    {
      printMbrObjDefn (out, entity.getObj (), ns, qual_name);
    }
}
namespace
{
  void PrintMbrDefn::visit (FuncDefnEntity const & entity) const
    {
      printMbrFuncDefn (out, entity.getFuncDefn (), ns, qual_name);
    }
}
namespace
{
  void PrintMbrDefn::visit (TmplFuncDefnEntity const & entity) const
    {
      printMbrTmplFuncDefn (out, entity.getTmplFuncDefn (), ns, qual_name);
    }
}
namespace
{
  void PrintMbrDefn::visit (ClassDefnEntity const & entity) const
    {
   // printMbrDefn (out, entity.getClassDefn (), ns, qual_name);
      printMbrDefn (out, entity.getClassDefn (), ns);
    }
}
namespace
{
  void PrintMbrDefn::visit (TmplClassDefnEntity const & entity) const
    {
   // printTmplMbrDefn (out, entity.getTmplClassDefn (), ns, qual_name);
      printTmplMbrDefn (out, entity.getTmplClassDefn (), ns);
    }
}
namespace
{
  void PrintMbrDefn::visitEntitySet (EntityPtrDeque const & entity_set, Output & out, NsPtr const & ns, NamePtr const & qual_name)
    {
      std::for_each (entity_set.begin (), entity_set.end (), AcceptEntityVisitor (PrintMbrDefn (out, ns, qual_name)));
    }
}
namespace
{
  void PrintMbrDefn::visit (NavSubmitFuncDefnEntity const & entity) const
    {
      printNavSubmitFuncDefn (out, entity.getNavSubmitFuncDefn (), ns, qual_name);
    }
}
namespace
{
  LZZ_INLINE PrintMbrDefn::PrintMbrDefn (Output & out, NsPtr const & ns, NamePtr const & qual_name)
    : out (out), ns (ns), qual_name (qual_name)
         {}
}
namespace
{
  PrintMbrDefn::~ PrintMbrDefn ()
         {}
}
namespace smtc
{
  void printMbrDefn (Output & out, ClassDefnPtr const & class_defn, NsPtr const & ns)
  {
    EntityPtrDeque const & entity_set = class_defn->getEntitySet ();
 // PrintMbrDefn::visitEntitySet (entity_set, out, ns, class_defn->getName ());
    PrintMbrDefn::visitEntitySet (entity_set, out, ns, class_defn->getQualName ());
  }
}
#undef LZZ_INLINE
