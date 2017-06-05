// gram_GetNodeBlockSet.cpp
//

#include "gram_GetNodeBlockSet.h"
// gram
#include "gram_BlockTable.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeBlockSet : Visitor
  {
    BlockVector & block_set;
    void visit (BlockNode & node) const;
  public:
    explicit GetNodeBlockSet (BlockVector & block_set);
    ~ GetNodeBlockSet ();
  };
}
namespace
{
  void GetNodeBlockSet::visit (BlockNode & node) const
    {
      // trim block (in vdf direct obj inits: so the right paren and semi appear on the same line)
      Block block = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      block.trim ();
      block_set.push_back (block);
    }
}
namespace
{
  LZZ_INLINE GetNodeBlockSet::GetNodeBlockSet (BlockVector & block_set)
    : block_set (block_set)
         {}
}
namespace
{
  GetNodeBlockSet::~ GetNodeBlockSet ()
         {}
}
namespace gram
{
  void getNodeBlockSet (basl::Nonterm & node, BlockVector & block_set)
  {
    node.accept (GetNodeBlockSet (block_set));
  }
}
#undef LZZ_INLINE
