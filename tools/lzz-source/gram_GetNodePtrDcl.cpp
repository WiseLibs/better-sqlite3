// gram_GetNodePtrDcl.cpp
//

#include "gram_GetNodePtrDcl.h"
// gram
#include "gram_GetNodeCvSpecSeq.h"
#include "gram_GetNodeName.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_GetCv.h"
#include "smtc_GetCvType.h"
#include "smtc_GetMbrPtrType.h"
#include "smtc_GetPtrType.h"
#include "smtc_GetRefType.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodePtrDcl : Visitor
  {
    smtc::CvType & cv_type;
    void visit (PtrOper1Node & node) const;
    void visit (PtrOper2Node & node) const;
    void visit (PtrOper3Node & node) const;
  public:
    explicit GetNodePtrDcl (smtc::CvType & cv_type);
    ~ GetNodePtrDcl ();
  };
}
namespace
{
  void GetNodePtrDcl::visit (PtrOper1Node & node) const
    {
      smtc::Cv cv = getNodeCvSpecSeq (node.getCvSpecSeqOpt ());
      cv_type = smtc::getCvType (smtc::getPtrType (cv_type), cv);
    }
}
namespace
{
  void GetNodePtrDcl::visit (PtrOper2Node & node) const
    {
      cv_type = smtc::getCvType (smtc::getRefType (cv_type), smtc::getCv (false, false));
    }
}
namespace
{
  void GetNodePtrDcl::visit (PtrOper3Node & node) const
    {
      smtc::NamePtr mbr_name = getNodeName (node.getObjName ());
      smtc::Cv cv = getNodeCvSpecSeq (node.getCvSpecSeqOpt ());
      cv_type = smtc::getCvType (smtc::getMbrPtrType (mbr_name, cv_type), cv);
    }
}
namespace
{
  LZZ_INLINE GetNodePtrDcl::GetNodePtrDcl (smtc::CvType & cv_type)
    : cv_type (cv_type)
         {}
}
namespace
{
  GetNodePtrDcl::~ GetNodePtrDcl ()
         {}
}
namespace gram
{
  void getNodePtrDcl (basl::Nonterm & nonterm, smtc::CvType & cv_type)
  {
    nonterm.accept (GetNodePtrDcl (cv_type));
  }
}
#undef LZZ_INLINE
