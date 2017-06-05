// gram_GetMbrInitSet.cpp
//

#include "gram_GetMbrInitSet.h"
// gram
#include "gram_BlockTable.h"
#include "gram_GetNodeBlockSet.h"
#include "gram_GetNodeName.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_GetMbrInit.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetMbrInitSet : Visitor
  {
    smtc::MbrInitPtrVector & mbr_init_set;
    void visit (MbrInitNode & node) const;
  public:
    explicit GetMbrInitSet (smtc::MbrInitPtrVector & mbr_init_set);
    ~ GetMbrInitSet ();
  };
}
namespace
{
  void GetMbrInitSet::visit (MbrInitNode & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      BlockVector arg_set;
      getNodeBlockSet (node.getExprListOpt (), arg_set);
      mbr_init_set.push_back (smtc::getMbrInit (name, arg_set));
    }
}
namespace
{
  LZZ_INLINE GetMbrInitSet::GetMbrInitSet (smtc::MbrInitPtrVector & mbr_init_set)
    : mbr_init_set (mbr_init_set)
         {}
}
namespace
{
  GetMbrInitSet::~ GetMbrInitSet ()
         {}
}
namespace gram
{
  void getMbrInitSet (basl::Nonterm & nonterm, smtc::MbrInitPtrVector & mbr_init_set)
  {
    nonterm.accept (GetMbrInitSet (mbr_init_set));
  }
}
#undef LZZ_INLINE
