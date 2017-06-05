// gram_GetTmplParamSet.cpp
//

#include "gram_GetTmplParamSet.h"
// gram
#include "gram_BlockTable.h"
#include "gram_GetNodeDcl.h"
#include "gram_GetNodeName.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_GetNonTypeParam.h"
#include "smtc_GetTmplParam.h"
#include "smtc_GetTypeParam.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetTmplParamSet : Visitor
  {
    smtc::ParamPtrVector & param_set;
    void visit (ParamDecl1Node & node) const;
    void visit (ParamDecl2Node & node) const;
    void visit (TypeParam1Node & node) const;
    void visit (TypeParam2Node & node) const;
    void visit (TmplTmplParam1Node & node) const;
    void visit (TmplTmplParam2Node & node) const;
  public:
    explicit GetTmplParamSet (smtc::ParamPtrVector & param_set);
    ~ GetTmplParamSet ();
  };
}
namespace
{
  void GetTmplParamSet::visit (ParamDecl1Node & node) const
    {
      SpecSel dcl_spec_sel;
      smtc::CvType cv_type;
      smtc::NamePtr name;
      getNodeParamDcl (node.getParamDecl (), dcl_spec_sel, cv_type, name);
      param_set.push_back (smtc::getNonTypeParam (dcl_spec_sel, cv_type, name, Block ()));
    }
}
namespace
{
  void GetTmplParamSet::visit (ParamDecl2Node & node) const
    {
      SpecSel dcl_spec_sel;
      smtc::CvType cv_type;
      smtc::NamePtr name;
      getNodeParamDcl (node.getParamDecl (), dcl_spec_sel, cv_type, name);
      Block defarg = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      param_set.push_back (smtc::getNonTypeParam (dcl_spec_sel, cv_type, name, defarg));
    }
}
namespace
{
  void GetTmplParamSet::visit (TypeParam1Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      param_set.push_back (smtc::getTypeParam (name, smtc::CvType ()));
    }
}
namespace
{
  void GetTmplParamSet::visit (TypeParam2Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::CvType def_type;
      getNodeAbstractDcl (node.getAbstractDecl (), def_type);
      param_set.push_back (smtc::getTypeParam (name, def_type));
    }
}
namespace
{
  void GetTmplParamSet::visit (TmplTmplParam1Node & node) const
    {
      smtc::ParamPtrVector nstd_param_set;
      getTmplParamSet (node.getTmplParamListOpt (), nstd_param_set);
      smtc::NamePtr name = getNodeName (node.getObjName ());
      param_set.push_back (smtc::getTmplParam (name, nstd_param_set, smtc::NamePtr ()));
    }
}
namespace
{
  void GetTmplParamSet::visit (TmplTmplParam2Node & node) const
    {
      smtc::ParamPtrVector nstd_param_set;
      getTmplParamSet (node.getTmplParamListOpt (), nstd_param_set);
      smtc::NamePtr name = getNodeName (node.getObjName1 ());
      smtc::NamePtr def_name = getNodeName (node.getObjName2 ());
      param_set.push_back (smtc::getTmplParam (name, nstd_param_set, def_name));
    }
}
namespace
{
  LZZ_INLINE GetTmplParamSet::GetTmplParamSet (smtc::ParamPtrVector & param_set)
    : Visitor (), param_set (param_set)
         {}
}
namespace
{
  GetTmplParamSet::~ GetTmplParamSet ()
         {}
}
namespace gram
{
  void getTmplParamSet (basl::Nonterm & nonterm, smtc::ParamPtrVector & param_set)
  {
    nonterm.accept (GetTmplParamSet (param_set));
  }
}
#undef LZZ_INLINE
