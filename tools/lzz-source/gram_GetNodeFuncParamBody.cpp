// gram_GetNodeFuncParamBody.cpp
//

#include "gram_GetNodeFuncParamBody.h"
// gram
#include "gram_GetNodeDcl.h"
#include "gram_GetNodeFuncParamSet.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeFuncParamBody : Visitor
  {
    smtc::ParamPtrVector & param_set;
    bool & vararg;
    void visit (ParamDeclBody1Node & node) const;
    void visit (ParamDeclBody2Node & node) const;
    void visit (ParamDeclBody3Node & node) const;
    void visit (ParamDeclBody4Node & node) const;
  public:
    explicit GetNodeFuncParamBody (smtc::ParamPtrVector & param_set, bool & vararg);
    ~ GetNodeFuncParamBody ();
  };
}
namespace
{
  void GetNodeFuncParamBody::visit (ParamDeclBody1Node & node) const
    {
      getNodeFuncParamSet (node.getParamDecl1List (), param_set);
      vararg = node.getEllipseOpt ().isSet ();
    }
}
namespace
{
  void GetNodeFuncParamBody::visit (ParamDeclBody2Node & node) const
    {
      getNodeFuncParamSet (node.getParamDecl1List (), param_set);
      vararg = true;
    }
}
namespace
{
  void GetNodeFuncParamBody::visit (ParamDeclBody3Node & node) const
    {
      vararg = node.getEllipseOpt ().isSet ();
    }
}
namespace
{
  void GetNodeFuncParamBody::visit (ParamDeclBody4Node & node) const
    {}
}
namespace
{
  LZZ_INLINE GetNodeFuncParamBody::GetNodeFuncParamBody (smtc::ParamPtrVector & param_set, bool & vararg)
    : Visitor (), param_set (param_set), vararg (vararg)
         {}
}
namespace
{
  GetNodeFuncParamBody::~ GetNodeFuncParamBody ()
         {}
}
namespace gram
{
  void getNodeFuncParamBody (basl::Nonterm & nonterm, smtc::ParamPtrVector & param_set, bool & vararg)
  {
    nonterm.accept (GetNodeFuncParamBody (param_set, vararg));
  }
}
#undef LZZ_INLINE
