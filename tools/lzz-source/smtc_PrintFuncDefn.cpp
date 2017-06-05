// smtc_PrintFuncDefn.cpp
//

#include "smtc_PrintFuncDefn.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintFuncDefn.inl"
#endif
// std lib
#include <algorithm>

// semantic
#include "smtc_CtorInit.h"
#include "smtc_CtorInitToString.h"
#include "smtc_FuncDefn.h"
#include "smtc_GetNameLoc.h"
#include "smtc_PrintCode.h"
#include "smtc_PrintHandler.h"
#include "smtc_PrintNsClose.h"
#include "smtc_PrintNsOpen.h"
#include "smtc_TryBlock.h"
#define LZZ_INLINE inline
namespace smtc
{
  void PrintFuncDefn::print (FilePtr const & file, SectionKind skind, FuncDefnPtr const & func_defn, NsPtr const & ns) const
    {
      int ns_depth = printNsOpen (file, skind, ns);
      print (file, skind, func_defn);
      printNsClose (file, skind, ns_depth);
    }
}
namespace smtc
{
  void PrintFuncDefn::print (FilePtr const & file, SectionKind skind, FuncDefnPtr const & func_defn) const
    {
      // declaration
      printLine (file, skind, getNameLoc (func_defn->getName ()), declToString (func_defn));
      // try
      TryBlockPtr const & try_block = func_defn->getTryBlock ();
      if (try_block.isSet ())
      {
        printLine (file, skind, try_block->getLoc (), "try");
      }
      // ctor init
      CtorInitPtr const & ctor_init = func_defn->getCtorInit ();
      if (ctor_init.isSet ())
      {
        printLine (file, skind, ctor_init->getLoc (), 1, ctorInitToString (ctor_init));
      }
      // body
      printEnclosedBlock (file, skind, func_defn->getBody ());
      // handler seq
      if (try_block.isSet ())
      {
        HandlerPtrVector const & handler_seq = try_block->getHandlerSeq ();
        std::for_each (handler_seq.begin (), handler_seq.end (), PrintHandler (file, skind));
      }
    }
}
#undef LZZ_INLINE
