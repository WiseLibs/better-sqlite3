// gram_GetNodeTypeIdSet.cpp
//

#include "gram_GetNodeTypeIdSet.h"
// gram
#include "gram_GetNodeDcl.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeTypeIdSet : Visitor
  {
    smtc::CvTypeVector & cv_type_set;
    void visit (TypeIdNode & node) const;
  public:
    explicit GetNodeTypeIdSet (smtc::CvTypeVector & cv_type_set);
    ~ GetNodeTypeIdSet ();
  };
}
namespace
{
  void GetNodeTypeIdSet::visit (TypeIdNode & node) const
    {
      smtc::CvType cv_type;
      getNodeAbstractDcl (node.getAbstractDecl (), cv_type);
      cv_type_set.push_back (cv_type);
    }
}
namespace
{
  LZZ_INLINE GetNodeTypeIdSet::GetNodeTypeIdSet (smtc::CvTypeVector & cv_type_set)
    : cv_type_set (cv_type_set)
         {}
}
namespace
{
  GetNodeTypeIdSet::~ GetNodeTypeIdSet ()
         {}
}
namespace gram
{
  void getNodeTypeIdSet (basl::Nonterm & nonterm, smtc::CvTypeVector & cv_type_set)
  {
    nonterm.accept (GetNodeTypeIdSet (cv_type_set));
  }
}
#undef LZZ_INLINE
