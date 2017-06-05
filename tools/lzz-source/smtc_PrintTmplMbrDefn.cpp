// smtc_PrintTmplMbrDefn.cpp
//

#include "smtc_PrintTmplMbrDefn.h"
// std lib
#include <algorithm>
 
// semantic
#include "smtc_AcceptEntityVisitor.h"
#include "smtc_ClassDefn.h"
#include "smtc_CreateQualName.h"
#include "smtc_EntityVisitor.h"
#include "smtc_IsExplicitTmplSpec.h"
#include "smtc_FormTmplName.h"
#include "smtc_PrintMbrTmplFuncDefn.h"
#include "smtc_PrintMbrTmplObjDefn.h"
#include "smtc_TmplClassDefn.h"
#include "smtc_TmplSpecToArgString.h"
#include "smtc_PrintMbrDefn.h"

// entities
#include "smtc_ClassDefnEntity.h"
#include "smtc_FuncDefnEntity.h"
#include "smtc_LazyClassEntity.h"
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
  struct PrintTmplMbrDefn : EntityVisitor
  {
    Output & out;
    TmplSpecPtrVector const & tmpl_spec_set;
    NsPtr const & ns;
    NamePtr const & qual_name;
    void visit (ObjEntity const & entity) const;
    void visit (FuncDefnEntity const & entity) const;
    void visit (TmplFuncDefnEntity const & entity) const;
    void visit (ClassDefnEntity const & entity) const;
    void visit (TmplClassDefnEntity const & entity) const;
    void visit (LazyClassEntity const & entity) const;
    static void visitEntitySet (EntityPtrDeque const & entity_set, Output & out, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name);
  public:
    explicit PrintTmplMbrDefn (Output & out, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name);
    ~ PrintTmplMbrDefn ();
  };
}
namespace
{
  void PrintTmplMbrDefn::visit (ObjEntity const & entity) const
    {
      printMbrTmplObjDefn (out, entity.getObj (), tmpl_spec_set, ns, qual_name);
    }
}
namespace
{
  void PrintTmplMbrDefn::visit (FuncDefnEntity const & entity) const
    {
      printMbrTmplFuncDefn (out, entity.getFuncDefn (), tmpl_spec_set, ns, qual_name);
    }
}
namespace
{
  void PrintTmplMbrDefn::visit (TmplFuncDefnEntity const & entity) const
    {
      printMbrTmplFuncDefn (out, entity.getTmplFuncDefn (), tmpl_spec_set, ns, qual_name);
    }
}
namespace
{
  void PrintTmplMbrDefn::visit (ClassDefnEntity const & entity) const
    {
      printTmplMbrDefn (out, entity.getClassDefn (), tmpl_spec_set, ns);
    }
}
namespace
{
  void PrintTmplMbrDefn::visit (TmplClassDefnEntity const & entity) const
    {
      printTmplMbrDefn (out, entity.getTmplClassDefn (), tmpl_spec_set, ns);
    }
}
namespace
{
  void PrintTmplMbrDefn::visit (LazyClassEntity const & entity) const
    {
      printTmplMbrDefn (out, entity.getLazyClass (), tmpl_spec_set, ns);
    }
}
namespace
{
  void PrintTmplMbrDefn::visitEntitySet (EntityPtrDeque const & entity_set, Output & out, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name)
    {
      std::for_each (entity_set.begin (), entity_set.end (), AcceptEntityVisitor (PrintTmplMbrDefn (out, tmpl_spec_set, ns, qual_name)));
    }
}
namespace
{
  LZZ_INLINE PrintTmplMbrDefn::PrintTmplMbrDefn (Output & out, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns, NamePtr const & qual_name)
    : out (out), tmpl_spec_set (tmpl_spec_set), ns (ns), qual_name (qual_name)
         {}
}
namespace
{
  PrintTmplMbrDefn::~ PrintTmplMbrDefn ()
         {}
}
namespace smtc
{
  void printTmplMbrDefn (Output & out, TmplClassDefnPtr const & tmpl_class_defn, NsPtr const & ns)
  {
    ClassDefnPtr class_defn = tmpl_class_defn->getClassDefn ();
    EntityPtrDeque const & entity_set = class_defn->getEntitySet ();
    TmplSpecPtrVector const & tmpl_spec_set = tmpl_class_defn->getTmplSpecSet ();
    if (isExplicitTmplSpec (tmpl_spec_set))
    {
      printMbrDefn (out, tmpl_class_defn->getClassDefn (), ns);
    }
    else
    {
      // precede defintions with tmpl spec set
      PrintTmplMbrDefn::visitEntitySet (entity_set, out, tmpl_spec_set, ns, class_defn->getQualName ());
    }
  }
}
namespace smtc
{
  void printTmplMbrDefn (Output & out, TmplClassDefnPtr const & tmpl_class_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns)
  {
    ClassDefnPtr class_defn = tmpl_class_defn->getClassDefn ();
    EntityPtrDeque const & entity_set = class_defn->getEntitySet ();
    TmplSpecPtrVector full_tmpl_spec_set (tmpl_class_defn->getTmplSpecSet ());
    full_tmpl_spec_set.insert (full_tmpl_spec_set.end (), tmpl_spec_set.begin (), tmpl_spec_set.end ());
    PrintTmplMbrDefn::visitEntitySet (entity_set, out, full_tmpl_spec_set, ns, class_defn->getQualName ());
  }
}
namespace smtc
{
  void printTmplMbrDefn (Output & out, ClassDefnPtr const & class_defn, TmplSpecPtrVector const & tmpl_spec_set, NsPtr const & ns)
  {
    EntityPtrDeque const & entity_set = class_defn->getEntitySet ();
    PrintTmplMbrDefn::visitEntitySet (entity_set, out, tmpl_spec_set, ns, class_defn->getQualName ());
  }
}
#undef LZZ_INLINE
