// gram_GetNodeDcl.cpp
//

#include "gram_GetNodeDcl.h"
// gram
#include "gram_BlockTable.h"
#include "gram_DclSpecFlags.h"
#include "gram_DeclareNodeSimpleDecl.h"
#include "gram_GetNodeCvSpecSeq.h"
#include "gram_GetNodeDeclSpec.h"
#include "gram_GetNodeFuncParamBody.h"
#include "gram_GetNodeName.h"
#include "gram_GetNodePtrDcl.h"
#include "gram_GetNodeTypeIdSet.h"
#include "gram_Nonterm.h"
#include "gram_Parser.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_CreateThrowSpec.h"
#include "smtc_GetArrayType.h"
#include "smtc_GetCv.h"
#include "smtc_GetCvType.h"
#include "smtc_GetFuncType.h"

// basil
#include "basl_Node.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeDcl : Visitor
  {
    SpecSel & decl_spec_sel;
    SpecSel & dcl_spec_sel;
    smtc::CvType & cv_type;
    smtc::CvType & dcl_cv_type;
    smtc::NamePtr & name;
    void visit (Decl1Node & node) const;
    void visit (Decl2Node & node) const;
    void visit (PureDclNode & node) const;
    void visit (DclNode & node) const;
    void visit (DirectDcl1Node & node) const;
    void visit (DirectDcl6Node & node) const;
    void visit (DirectDcl2Node & node) const;
    void visit (DirectDcl3Node & node) const;
    void visit (IdNode & node) const;
  public:
    explicit GetNodeDcl (SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name);
    ~ GetNodeDcl ();
  };
}
namespace
{
  struct GetNodeObjDcl : GetNodeDcl
  {
    smtc::ScopePtr const & cs;
    void visit (NestedDeclNode & node) const;
  public:
    explicit GetNodeObjDcl (smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name);
    ~ GetNodeObjDcl ();
  };
}
namespace
{
  struct GetNodeFuncDcl : GetNodeObjDcl
  {
    smtc::ParamPtrVector & param_set;
    bool & vararg;
    smtc::Cv & cv;
    smtc::ThrowSpecPtr & throw_spec;
    void visit (DirectDcl4Node & node) const;
  public:
    explicit GetNodeFuncDcl (smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::ParamPtrVector & param_set, bool & vararg, smtc::Cv & cv, smtc::ThrowSpecPtr & throw_spec);
    ~ GetNodeFuncDcl ();
  };
}
namespace
{
  struct GetNodeFunctorDcl : GetNodeObjDcl
  {
    smtc::ParamPtrVector & ctor_param_set;
    bool & ctor_vararg;
    smtc::ParamPtrVector & call_param_set;
    bool & call_vararg;
    smtc::Cv & cv;
    smtc::ThrowSpecPtr & throw_spec;
    void visit (DirectDcl5Node & node) const;
  public:
    explicit GetNodeFunctorDcl (smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::ParamPtrVector & ctor_param_set, bool & ctor_vararg, smtc::ParamPtrVector & call_param_set, bool & call_vararg, smtc::Cv & cv, smtc::ThrowSpecPtr & throw_spec);
    ~ GetNodeFunctorDcl ();
  };
}
namespace
{
  struct GetNodeNavDcl : GetNodeDcl
  {
    smtc::CvType & node_cv_type;
    smtc::ParamPtrVector & param_set;
    bool & vararg;
    void visit (NavDirectDcl1Node & node) const;
  public:
    explicit GetNodeNavDcl (SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::CvType & node_cv_type, smtc::ParamPtrVector & param_set, bool & vararg);
    ~ GetNodeNavDcl ();
  };
}
namespace
{
  void GetNodeDcl::visit (Decl1Node & node) const
    {
      dcl_cv_type = cv_type;
      node.getPureCtorDcl ().accept (* this);
    }
}
namespace
{
  void GetNodeDcl::visit (Decl2Node & node) const
    {
      getNodeDeclSpec (node.getXBxxDeclSpecSeq (), decl_spec_sel, dcl_spec_sel, cv_type);
      dcl_cv_type = cv_type;
      node.getObjDcl ().accept (* this);
    }
}
namespace
{
  void GetNodeDcl::visit (PureDclNode & node) const
    {
      basl::Nonterm & pure_node = node.getPureOpt ();
      if (pure_node.isSet ())
      {
        dcl_spec_sel.addSpec (PURE_SPEC, PureNode (pure_node).getASSIGN_TOKEN ().getLoc ());
      }
      node.getFuncDcl ().accept (* this);
    }
}
namespace
{
  void GetNodeDcl::visit (DclNode & node) const
    {
      getNodePtrDcl (node.getPtrOper (), dcl_cv_type);
      node.getObjADcl ().accept (* this);
    }
}
namespace
{
  void GetNodeDcl::visit (DirectDcl1Node & node) const
    {
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      getNodeFuncParamBody (node.getParamDecl1Body (), param_set, vararg);
      smtc::Cv cv = getNodeCvSpecSeq (node.getCvSpecSeqOpt ());
      smtc::ThrowSpecPtr throw_spec;
      basl::Nonterm & throw_spec_node = node.getThrowSpecOpt ();
      if (throw_spec_node.isSet ())
      {
        smtc::CvTypeVector cv_type_set;
        getNodeTypeIdSet (node.getThrowSpecOpt (), cv_type_set);
        throw_spec = smtc::createThrowSpec (cv_type_set);
      }
      dcl_cv_type = smtc::getFuncType (dcl_cv_type, param_set, vararg, cv, throw_spec);
      node.getObjBDirectDcl ().accept (* this);
    }
}
namespace
{
  void GetNodeDcl::visit (DirectDcl6Node & node) const
    {
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      visitVdfDataParamList (node.getVdfDataParamList (), param_set, vararg);
      smtc::Cv cv = getNodeCvSpecSeq (node.getCvSpecSeqOpt ());
      smtc::ThrowSpecPtr throw_spec;
      basl::Nonterm & throw_spec_node = node.getThrowSpecOpt ();
      if (throw_spec_node.isSet ())
      {
        smtc::CvTypeVector cv_type_set;
        getNodeTypeIdSet (node.getThrowSpecOpt (), cv_type_set);
        throw_spec = smtc::createThrowSpec (cv_type_set);
      }
      dcl_cv_type = smtc::getFuncType (dcl_cv_type, param_set, vararg, cv, throw_spec);
      node.getVdfObjBDirectDcl ().accept (* this);
    }
}
namespace
{
  void GetNodeDcl::visit (DirectDcl2Node & node) const
    {
      util::String size;
      basl::Token block_token = node.getBlockOpt ();
      if (block_token.isSet ())
      {
        size = getBlock (block_token.getLexeme ()).toString ();
      }
      dcl_cv_type = smtc::getCvType (smtc::getArrayType (dcl_cv_type, size), smtc::getCv (false, false));
      node.getObjADirectDcl ().accept (* this);
    }
}
namespace
{
  void GetNodeDcl::visit (DirectDcl3Node & node) const
    {
      node.getObjBDcl ().accept (* this);
    }
}
namespace
{
  void GetNodeDcl::visit (IdNode & node) const
    {
      name = getNodeName (node.getObjName ());
    }
}
namespace
{
  LZZ_INLINE GetNodeDcl::GetNodeDcl (SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name)
    : Visitor (), decl_spec_sel (decl_spec_sel), dcl_spec_sel (dcl_spec_sel), cv_type (cv_type), dcl_cv_type (dcl_cv_type), name (name)
         {}
}
namespace
{
  GetNodeDcl::~ GetNodeDcl ()
         {}
}
namespace
{
  void GetNodeObjDcl::visit (NestedDeclNode & node) const
    {
      declareNodeSimpleDecl (node.getNestedSimpleDecl (), cs, decl_spec_sel, dcl_spec_sel, cv_type);
      dcl_cv_type = cv_type;
      // remove pure spec in case set in previous declarator
      dcl_spec_sel.remSpec (PURE_SPEC);
      node.getObjDcl ().accept (* this);
    }
}
namespace
{
  LZZ_INLINE GetNodeObjDcl::GetNodeObjDcl (smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name)
    : GetNodeDcl (decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name), cs (cs)
         {}
}
namespace
{
  GetNodeObjDcl::~ GetNodeObjDcl ()
         {}
}
namespace
{
  void GetNodeFuncDcl::visit (DirectDcl4Node & node) const
    {
      getNodeFuncParamBody (node.getParamDecl1Body (), param_set, vararg);
      cv = getNodeCvSpecSeq (node.getCvSpecSeqOpt ());
      basl::Nonterm & throw_spec_node = node.getThrowSpecOpt ();
      if (throw_spec_node.isSet ())
      {
        smtc::CvTypeVector cv_type_set;
        getNodeTypeIdSet (node.getThrowSpecOpt (), cv_type_set);
        throw_spec = smtc::createThrowSpec (cv_type_set);
      }
      node.getObjDclId ().accept (* this);
    }
}
namespace
{
  LZZ_INLINE GetNodeFuncDcl::GetNodeFuncDcl (smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::ParamPtrVector & param_set, bool & vararg, smtc::Cv & cv, smtc::ThrowSpecPtr & throw_spec)
    : GetNodeObjDcl (cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name), param_set (param_set), vararg (vararg), cv (cv), throw_spec (throw_spec)
         {}
}
namespace
{
  GetNodeFuncDcl::~ GetNodeFuncDcl ()
         {}
}
namespace
{
  void GetNodeFunctorDcl::visit (DirectDcl5Node & node) const
    {
      getNodeFuncParamBody (node.getParamDecl1Body (), ctor_param_set, ctor_vararg);
      getNodeFuncParamBody (node.getParamDecl2Body (), call_param_set, call_vararg);
      cv = getNodeCvSpecSeq (node.getCvSpecSeqOpt ());
      basl::Nonterm & throw_spec_node = node.getThrowSpecOpt ();
      if (throw_spec_node.isSet ())
      {
        smtc::CvTypeVector cv_type_set;
        getNodeTypeIdSet (node.getThrowSpecOpt (), cv_type_set);
        throw_spec = smtc::createThrowSpec (cv_type_set);
      }
      node.getObjDclId ().accept (* this);
    }
}
namespace
{
  LZZ_INLINE GetNodeFunctorDcl::GetNodeFunctorDcl (smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::ParamPtrVector & ctor_param_set, bool & ctor_vararg, smtc::ParamPtrVector & call_param_set, bool & call_vararg, smtc::Cv & cv, smtc::ThrowSpecPtr & throw_spec)
    : GetNodeObjDcl (cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name), ctor_param_set (ctor_param_set), ctor_vararg (ctor_vararg), call_param_set (call_param_set), call_vararg (call_vararg), cv (cv), throw_spec (throw_spec)
         {}
}
namespace
{
  GetNodeFunctorDcl::~ GetNodeFunctorDcl ()
         {}
}
namespace
{
  void GetNodeNavDcl::visit (NavDirectDcl1Node & node) const
    {
      getNodeDeclSpec (node.getNavNodeType (), node_cv_type);
      getNodeFuncParamBody (node.getParamDecl1Body (), param_set, vararg);
      node.getObjDclId ().accept (* this);
    }
}
namespace
{
  LZZ_INLINE GetNodeNavDcl::GetNodeNavDcl (SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::CvType & node_cv_type, smtc::ParamPtrVector & param_set, bool & vararg)
    : GetNodeDcl (decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name), node_cv_type (node_cv_type), param_set (param_set), vararg (vararg)
         {}
}
namespace
{
  GetNodeNavDcl::~ GetNodeNavDcl ()
         {}
}
namespace gram
{
  void getNodeAbstractDcl (basl::Nonterm & nonterm, smtc::CvType & dcl_cv_type)
  {
    SpecSel decl_spec_sel, dcl_spec_sel;
    smtc::CvType cv_type;
    smtc::NamePtr name;
    nonterm.accept (GetNodeDcl (decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name));
  }
}
namespace gram
{
  void getNodeParamDcl (basl::Nonterm & nonterm, SpecSel & dcl_spec_sel, smtc::CvType & dcl_cv_type, smtc::NamePtr & name)
  {
    SpecSel decl_spec_sel;
    smtc::CvType cv_type;
    nonterm.accept (GetNodeDcl (decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name));
  }
}
namespace gram
{
  void getNodeObjDcl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name)
  {
    nonterm.accept (GetNodeObjDcl (cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name));
  }
}
namespace gram
{
  void getNodeFuncDcl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::ParamPtrVector & param_set, bool & vararg, smtc::Cv & cv, smtc::ThrowSpecPtr & throw_spec)
  {
    nonterm.accept (GetNodeFuncDcl (cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name, param_set, vararg, cv, throw_spec));
  }
}
namespace gram
{
  void getNodeFunctorDcl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::ParamPtrVector & ctor_param_set, bool & ctor_vararg, smtc::ParamPtrVector & call_param_set, bool & call_vararg, smtc::Cv & cv, smtc::ThrowSpecPtr & throw_spec)
  {
    nonterm.accept (GetNodeFunctorDcl (cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name, ctor_param_set, ctor_vararg,
        call_param_set, call_vararg, cv, throw_spec));
  }
}
namespace gram
{
  void getNodeNavDcl (basl::Nonterm & nonterm, SpecSel & dcl_spec_sel, smtc::CvType & ret_type, smtc::NamePtr & name, smtc::CvType & node_type, smtc::ParamPtrVector & param_set)
  {
    SpecSel decl_spec_sel;
    bool vararg = false;
    smtc::CvType cv_type;
    nonterm.accept (GetNodeNavDcl (decl_spec_sel, dcl_spec_sel, cv_type, ret_type, name, node_type, param_set, vararg));
  }
}
namespace gram
{
  void visitVdfDataParamList (basl::Nonterm & vdf_data_param_list, smtc::ParamPtrVector & param_set, bool & vararg)
  {
    if (vdf_data_param_list.isSet ())
    {
      VdfDataParamListNode node (vdf_data_param_list);
      basl::Token block_token = node.getBlockOpt ();
      if (block_token.isSet ())
      {
        // parse block as param-decl-3-body, start state 1
        Block block = getBlock (block_token.getLexeme ());
        // OK to use unset scope as no use is going be made of it 
        basl::SyntaxTree tree = parseString (block.toString (), block.getLoc (), 1, smtc::ScopePtr ());
        if (! tree.isEmpty ())
        {
          getNodeFuncParamBody (tree.getNode ().getNonterm (), param_set, vararg);
        }
      }
    }
  }
}
#undef LZZ_INLINE
