// smtc_CompleteLazyClass.cpp
//

#include "smtc_CompleteLazyClass.h"
// semantic
#include "smtc_CreateAccessSpec.h"
#include "smtc_CreateAccessSpecEntity.h"
#include "smtc_CreateCtorInit.h"
#include "smtc_CreateFuncDefn.h"
#include "smtc_CreateFuncDefnEntity.h"
#include "smtc_CvType.h"
#include "smtc_GetNameLoc.h"
#include "smtc_GetUnqlNameAsDtor.h"
#include "smtc_GetUnqlNamePart.h"
#include "smtc_LazyClass.h"
#include "smtc_Linkage.h"
#include "smtc_SpecFlags.h"

// gram
#include "gram_CharBlock.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  void defineLazyClassCtor (LazyClassPtr const & lazy_class, util::Loc const & loc, NamePtr const & unql_name);
}
namespace
{
  void defineLazyClassDtor (LazyClassPtr const & lazy_class, util::Loc const & loc, NamePtr const & unql_name);
}
namespace
{
  void defineLazyClassCtor (LazyClassPtr const & lazy_class, util::Loc const & loc, NamePtr const & unql_name)
  {
    int flags = INLINE_SPEC|EXPLICIT_SPEC;
    CvType ret_type;
    ParamPtrVector const & param_set = lazy_class->getParamSet ();
    bool vararg = lazy_class->hasVarArg ();
    CtorInitPtr ctor_init;
    MbrInitPtrVector const & mbr_init_set = lazy_class->getMbrInitSet ();
    if (! mbr_init_set.empty ())
    {
      ctor_init = createCtorInit (loc, mbr_init_set);
    }
    gram::CharBlock body (loc);
    Cv cv;
    ThrowSpecPtr throw_spec;
    TryBlockPtr try_block;
    FuncDefnPtr func_defn = createFuncDefn (Linkage (), flags, ret_type, unql_name, param_set, vararg, cv, throw_spec, ctor_init, body, try_block);
    lazy_class->addEntity (createFuncDefnEntity (func_defn));
  }
}
namespace
{
  void defineLazyClassDtor (LazyClassPtr const & lazy_class, util::Loc const & loc, NamePtr const & unql_name)
  {
    int flags = 0;
    if (lazy_class->hasVirtualDtor ())
    {
      flags |= VIRTUAL_SPEC;
    }
    CvType ret_type;
    ParamPtrVector param_set;
    bool vararg = false;
    NamePtr name = getUnqlNameAsDtor (unql_name);
    CtorInitPtr ctor_init;
    gram::CharBlock body (loc);
    Cv cv;
    ThrowSpecPtr throw_spec;
    TryBlockPtr try_block;
    FuncDefnPtr func_defn = createFuncDefn (Linkage (), flags, ret_type, name, param_set, vararg, cv, throw_spec, ctor_init, body, try_block);
    lazy_class->addEntity (createFuncDefnEntity (func_defn));
  }
}
namespace smtc
{
  void completeLazyClass (LazyClassPtr const & lazy_class)
  {
    // get unql part of name
    NamePtr unql_name = getUnqlNamePart (lazy_class->getName ());
    // make sure ctor and dtor are public
    util::Loc loc = getNameLoc (unql_name);
    lazy_class->addEntity (createAccessSpecEntity (createAccessSpec (loc, PUBLIC_ACCESS)));
    // define ctor
    defineLazyClassCtor (lazy_class, loc, unql_name);
    // define dtor
    defineLazyClassDtor (lazy_class, loc, unql_name);
  }
}
#undef LZZ_INLINE
