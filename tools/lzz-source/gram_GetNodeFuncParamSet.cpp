// gram_GetNodeFuncParamSet.cpp
//

#include "gram_GetNodeFuncParamSet.h"
// gram
#include "gram_BlockTable.h"
#include "gram_GetNodeDcl.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_GetFuncParam.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeFuncParamSet : Visitor
  {
    smtc::ParamPtrVector & param_set;
    void visit (ParamDecl1Node & node) const;
    void visit (ParamDecl2Node & node) const;
  public:
    explicit GetNodeFuncParamSet (smtc::ParamPtrVector & param_set);
    ~ GetNodeFuncParamSet ();
  };
}
namespace
{
  void GetNodeFuncParamSet::visit (ParamDecl1Node & node) const
    {
      SpecSel dcl_spec_sel;
      smtc::CvType cv_type;
      smtc::NamePtr name;
      getNodeParamDcl (node.getParamDecl (), dcl_spec_sel, cv_type, name);
      param_set.push_back (smtc::getFuncParam (dcl_spec_sel, cv_type, name, Block ()));
    }
}
namespace
{
  void GetNodeFuncParamSet::visit (ParamDecl2Node & node) const
    {
      SpecSel dcl_spec_sel;
      smtc::CvType cv_type;
      smtc::NamePtr name;
      getNodeParamDcl (node.getParamDecl (), dcl_spec_sel, cv_type, name);
      Block defarg = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      param_set.push_back (smtc::getFuncParam (dcl_spec_sel, cv_type, name, defarg));
    }
}
namespace
{
  LZZ_INLINE GetNodeFuncParamSet::GetNodeFuncParamSet (smtc::ParamPtrVector & param_set)
    : Visitor (), param_set (param_set)
         {}
}
namespace
{
  GetNodeFuncParamSet::~ GetNodeFuncParamSet ()
         {}
}
namespace gram
{
  void getNodeFuncParamSet (basl::Nonterm & nonterm, smtc::ParamPtrVector & param_set)
  {
    nonterm.accept (GetNodeFuncParamSet (param_set));
  }
}
#undef LZZ_INLINE
