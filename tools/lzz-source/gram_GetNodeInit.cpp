// gram_GetNodeInit.cpp
//

#include "gram_GetNodeInit.h"
// gram
#include "gram_BlockTable.h"
#include "gram_GetNodeBlockSet.h"
#include "gram_Nonterm.h"
#include "gram_Parser.h"
#include "gram_Visitor.h"

// basil
#include "basl_GetFirstToken.h"
#include "basl_Node.h"

// semantic
#include "smtc_CreateCopyInit.h"
#include "smtc_CreateDirectInit.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeInit : Visitor
  {
    smtc::InitPtr & init;
    void visit (ObjInit1Node & node) const;
    void visit (ObjInit2Node & node) const;
    void visit (ObjInit3Node & node) const;
    void visit (ObjInit4Node & node) const;
  public:
    explicit GetNodeInit (smtc::InitPtr & init);
    ~ GetNodeInit ();
  };
}
namespace
{
  void GetNodeInit::visit (ObjInit1Node & node) const
    {
      Block block = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      block.setLoc (node.getASSIGN_TOKEN ().getLoc ());
      init = smtc::createCopyInit (node.getASSIGN_TOKEN ().getLoc (), block);
    }
}
namespace
{
  void GetNodeInit::visit (ObjInit2Node & node) const
    {
      BlockVector block_set;
      getNodeBlockSet (node.getExprList (), block_set);
      init = smtc::createDirectInit (node.getDINIT_TOKEN ().getLoc (), block_set);
    }
}
namespace
{
  void GetNodeInit::visit (ObjInit3Node & node) const
    {
      BlockVector block_set;
      getNodeBlockSet (node.getDirectExprList (), block_set);
      init = smtc::createDirectInit (basl::getFirstLoc (node.getDirectExprList ()), block_set);
    }
}
namespace
{
  void GetNodeInit::visit (ObjInit4Node & node) const
    {
      // parse block as expr-list, start state 2
      Block block = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      // OK to use unset scope as it won't be used by anything
      basl::SyntaxTree tree = parseString (block.toString (), block.getLoc (), 2, smtc::ScopePtr ());
      if (! tree.isEmpty ())
      {
        BlockVector block_set;
        getNodeBlockSet (tree.getNode ().getNonterm (), block_set);
        init = smtc::createDirectInit (node.getLPAREN_TOKEN ().getLoc (), block_set);
      }
    }
}
namespace
{
  LZZ_INLINE GetNodeInit::GetNodeInit (smtc::InitPtr & init)
    : init (init)
         {}
}
namespace
{
  GetNodeInit::~ GetNodeInit ()
         {}
}
namespace gram
{
  smtc::InitPtr getNodeInit (basl::Nonterm & nonterm)
  {
    smtc::InitPtr init;
    nonterm.accept (GetNodeInit (init));
    return init;
  }
}
#undef LZZ_INLINE
