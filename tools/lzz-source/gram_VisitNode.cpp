// gram_VisitNode.cpp
//

#include "gram_VisitNode.h"
// gram
#include "gram_BlockTable.h"
#include "gram_CharBlock.h"
#include "gram_DeclSpecFlags.h"
#include "gram_DeclareNodeSimpleDecl.h"
#include "gram_GetAccess.h"
#include "gram_GetBaseSpecSet.h"
#include "gram_GetBaseSpecSet.h"
#include "gram_GetClassKey.h"
#include "gram_GetElabType.h"
#include "gram_GetEnumtorSet.h"
#include "gram_GetHandlerSet.h"
#include "gram_GetMbrInitSet.h"
#include "gram_GetNodeBlockSet.h"
#include "gram_GetNodeDcl.h"
#include "gram_GetNodeDeclSpec.h"
#include "gram_GetNodeFuncParamBody.h"
#include "gram_GetNodeInit.h"
#include "gram_GetNodeName.h"
#include "gram_GetNodeTypeIdSet.h"
#include "gram_GetTmplParamSet.h"
#include "gram_Message.h"
#include "gram_Nonterm.h"
#include "gram_RemoveQuotes.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_CreateCtorInit.h"
#include "smtc_CreateDirectInit.h"
#include "smtc_CreateThrowSpec.h" 
#include "smtc_CreateTryBlock.h"
#include "smtc_DeclareAccessSpec.h"
#include "smtc_DeclareClass.h"
#include "smtc_DeclareFunctor.h"
#include "smtc_DeclareUsing.h"
#include "smtc_DeclareUsingDir.h"
#include "smtc_DefineClass.h"
#include "smtc_DefineEnum.h"
#include "smtc_DefineFunc.h"
#include "smtc_DefineFunctor.h"
#include "smtc_DefineLazyClass.h"
#include "smtc_DefineNavClass.h"
#include "smtc_DefineNavVisitFunc.h"
#include "smtc_DefineNs.h"
#include "smtc_DefineVdf.h"
#include "smtc_DefineVdfBlockData.h"
#include "smtc_DefineVdfFunctor.h"
#include "smtc_DefineVdfShortData.h"
#include "smtc_GetNameLoc.h"
#include "smtc_OpenLinkageBlock.h"
#include "smtc_OpenLinkageSpec.h"
#include "smtc_OpenTmplInst.h"
#include "smtc_OpenTmplSpec.h"
#include "smtc_SetReturnStmt.h"

// basil
#include "basl_GetFirstToken.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct VisitNode : Visitor
  {
    smtc::ScopePtrDeque & ss;
    smtc::ScopePtr const & cs;
    void visit (NamespaceHead1Node & node) const;
    void visit (NamespaceHead2Node & node) const;
    void visit (NamespaceDefNode & node) const;
    void visit (SimpleDeclNode & node) const;
    void visit (ClassDeclNode & node) const;
    void visit (FriendClassDeclNode & node) const;
    void visit (ClassHeadNode & node) const;
    void visit (ClassDefNode & node) const;
    void visitTryBlock (basl::Token & try_opt, basl::Nonterm & handler_seq_opt, smtc::TryBlockPtr & try_block) const;
    void visit (FuncDefNode & node) const;
    void visit (TmplSpecNode & node) const;
    void visit (TmplDeclNode & node) const;
    void visit (AccessSpecNode & node) const;
    void visit (TmplInstNode & node) const;
    void visit (TmplInstBeginNode & node) const;
    void visit (LazyCtorBegin1Node & node) const;
    void visit (LazyCtorNode & node) const;
    void visit (FunctorDefNode & node) const;
    void visit (FunctorDeclTypeNode & node) const;
    void visit (EnumDefNode & node) const;
    void visit (UsingDeclNode & node) const;
    void visit (UsingDirNode & node) const;
    void visit (LinkageSpecNode & node) const;
    void visit (LinkageBlockBeginNode & node) const;
    void visit (LinkageDeclBeginNode & node) const;
    void visit (NavDefNode & node) const;
    void visit (NavHeadNode & node) const;
    void visit (NavVisitFuncDefNode & node) const;
    void visit (ReturnStmtNode & node) const;
    void visit (VdfDefNode & node) const;
    void visit (VdfHeadNode & node) const;
    void visit (VdfFunctorDefNode & node) const;
    void visit (VdfShortData1DefNode & node) const;
    void visit (VdfShortData2DefNode & node) const;
    void visit (VdfBlockDataDefNode & node) const;
    void visit (VdfBlockDataHead1Node & node) const;
    void visit (VdfBlockDataHead2Node & node) const;
  public:
    explicit VisitNode (smtc::ScopePtrDeque & ss, smtc::ScopePtr const & cs);
    ~ VisitNode ();
  };
}
namespace
{
  void VisitNode::visit (NamespaceHead1Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::ScopePtr res_scope = smtc::defineNs (cs, node.getNAMESPACE_TOKEN ().getLoc (), name);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (NamespaceHead2Node & node) const
    {
      smtc::ScopePtr res_scope = smtc::defineUnnamedNs (cs, node.getNAMESPACE_TOKEN ().getLoc ());
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (NamespaceDefNode & node) const
    {
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visit (SimpleDeclNode & node) const
    {
      // declare simple decl
      declareNodeSimpleDecl (node.getNestedSimpleDecl (), cs);
    }
}
namespace
{
  void VisitNode::visit (ClassDeclNode & node) const
    {
      smtc::ClassKey key;
      smtc::NamePtr name;
      bool is_dll_api = false;
      getElabType (node.getXExxDeclSpecSeq (), key, name, is_dll_api);
      if (key == smtc::ENUM_KEY || key == smtc::TYPENAME_KEY)
      {
        util::Loc loc = smtc::getNameLoc (name);
        key == smtc::ENUM_KEY ? msg::enumDecl (loc) : msg::typenameDecl (loc);
      }
      else
      {
        smtc::declareClass (cs, key, name, is_dll_api);
      }
    }
}
namespace
{
  void VisitNode::visit (FriendClassDeclNode & node) const
    {
      smtc::ClassKey key;
      smtc::NamePtr name;
      getElabType (node.getFExxDeclSpecSeq (), key, name);
      if (key == smtc::ENUM_KEY || key == smtc::TYPENAME_KEY)
      {
        util::Loc loc = smtc::getNameLoc (name);
        key == smtc::ENUM_KEY ? msg::friendEnumDecl (loc) : msg::friendTypenameDecl (loc);
      }
      else
      {
        smtc::declareFrndClass (cs, key, name);
      }
    }
}
namespace
{
  void VisitNode::visit (ClassHeadNode & node) const
    {
      smtc::ClassKey key = getClassKey (node.getClassKey ().getNumber ());
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::BaseSpecPtrVector base_spec_set;
      getBaseSpecSet (node.getBaseClauseOpt (), base_spec_set);
      smtc::ScopePtr res_scope = smtc::defineClass (cs, key, name, node.getDllApiOpt ().isSet (), base_spec_set);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (ClassDefNode & node) const
    {
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visitTryBlock (basl::Token & try_opt, basl::Nonterm & handler_seq_opt, smtc::TryBlockPtr & try_block) const
    {
      if (try_opt.isSet ())
      {
        if (handler_seq_opt.isSet ())
        {
          smtc::HandlerPtrVector handler_set;
          getHandlerSet (handler_seq_opt, handler_set);
          try_block = smtc::createTryBlock (try_opt.getLoc (), handler_set);
        }
        else
        {
          msg::missingHandlerSeq (try_opt.getLoc ());
        }
      }
      else if (handler_seq_opt.isSet ())
      {
        msg::missingTry (basl::getFirstLoc (handler_seq_opt));
      }
    }
}
namespace
{
  void VisitNode::visit (FuncDefNode & node) const
    {
      // decl
      SpecSel decl_spec_sel, dcl_spec_sel;
      smtc::CvType cv_type, dcl_cv_type;
      smtc::NamePtr name;
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      smtc::Cv cv;
      smtc::ThrowSpecPtr throw_spec;
      getNodeFuncDcl (node.getFuncDecl (), cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name,
          param_set, vararg, cv, throw_spec);
      // ctor init
      smtc::CtorInitPtr ctor_init;
      basl::Nonterm & ctor_init_node = node.getCtorInitOpt ();
      if (ctor_init_node.isSet ())
      {
        smtc::MbrInitPtrVector mbr_init_set;
        getMbrInitSet (ctor_init_node, mbr_init_set);
        ctor_init = smtc::createCtorInit (basl::getFirstLoc (ctor_init_node), mbr_init_set);
      }
      // try block
      smtc::TryBlockPtr try_block;
      visitTryBlock (node.getTryOpt (), node.getHandlerSeqOpt (), try_block);
      // body
      Block body;
      basl::Token block_token = node.getBlockOpt ();
      if (block_token.isSet ())
      {
        body = getBlock (block_token.getLexeme ());
      }
      else
      {
        body = CharBlock (util::Loc ());
      }
      body.setLoc (node.getLBRACE_TOKEN ().getLoc ());
      if (decl_spec_sel.hasSpec (TYPEDEF_SPEC))
      {
        msg::typedefFuncDefn (decl_spec_sel.getSpecLoc (TYPEDEF_SPEC));
      }
      else if (decl_spec_sel.hasSpec (FRIEND_SPEC))
      {
        smtc::defineFrndFunc (cs, dcl_spec_sel, dcl_cv_type, name, param_set, vararg, cv, throw_spec, ctor_init, body, try_block);
      }
      else
      {
        smtc::defineFunc (cs, dcl_spec_sel, dcl_cv_type, name, param_set, vararg, cv, throw_spec, ctor_init, body, try_block);
      }
    }
}
namespace
{
  void VisitNode::visit (TmplSpecNode & node) const
    {
      smtc::ParamPtrVector param_set;
      getTmplParamSet (node.getTmplParamListOpt (), param_set);
      smtc::ScopePtr res_scope = smtc::openTmplSpec (cs, node.getTEMPLATE_TOKEN ().getLoc (), param_set);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (TmplDeclNode & node) const
    {
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visit (AccessSpecNode & node) const
    {
      smtc::Access access = getAccess (node.getAccess ().getNumber ());
      smtc::declareAccessSpec (cs, node.getAccess ().getLoc (), access);
    }
}
namespace
{
  void VisitNode::visit (TmplInstNode & node) const
    {
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visit (TmplInstBeginNode & node) const
    {
      smtc::ScopePtr res_scope = smtc::openTmplInst (cs);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (LazyCtorBegin1Node & node) const
    {
      SpecSel spec_sel;
      smtc::ClassKey key = getClassKey (node.getClassKey ().getNumber ());
      smtc::NamePtr name = getNodeName (node.getObjName ());
      bool is_dll_api = node.getDllApiOpt ().isSet ();
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      getNodeFuncParamBody (node.getParamDecl1Body (), param_set, vararg);
      smtc::BaseSpecPtrVector base_spec_set;
      getBaseSpecSet (node.getLazyBaseClauseOpt (), base_spec_set);
      smtc::ScopePtr res_scope = smtc::defineLazyClass (cs, spec_sel, key, name, is_dll_api, param_set, vararg, base_spec_set);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (LazyCtorNode & node) const
    {
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visit (FunctorDefNode & node) const
    {
      // decl
      SpecSel decl_spec_sel, dcl_spec_sel;
      smtc::CvType cv_type, dcl_cv_type;
      smtc::NamePtr name;
      smtc::ParamPtrVector ctor_param_set;
      bool ctor_vararg = false;
      smtc::ParamPtrVector call_param_set;
      bool call_vararg = false;
      smtc::Cv cv;
      smtc::ThrowSpecPtr throw_spec;
      getNodeFunctorDcl (node.getFunctorDecl (), cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name,
          ctor_param_set, ctor_vararg, call_param_set, call_vararg, cv, throw_spec);
      // base spec set
      smtc::BaseSpecPtrVector base_spec_set;
      getBaseSpecSet (node.getLazyBaseClauseOpt (), base_spec_set);
      // try block
      smtc::TryBlockPtr try_block;
      visitTryBlock (node.getTryOpt (), node.getHandlerSeqOpt (), try_block);
      // body
      Block body;
      basl::Token block_token = node.getBlockOpt ();
      if (block_token.isSet ())
      {
        body = getBlock (block_token.getLexeme ());
      }
      else
      {
        body = CharBlock (util::Loc ());
      }
      body.setLoc (node.getLBRACE_TOKEN ().getLoc ());
      smtc::defineFunctor (cs, dcl_spec_sel, dcl_cv_type, name, ctor_param_set, ctor_vararg, call_param_set, call_vararg, cv, throw_spec,
          base_spec_set, body, try_block);
    }
}
namespace
{
  void VisitNode::visit (FunctorDeclTypeNode & node) const
    {
      // decl
      SpecSel decl_spec_sel, dcl_spec_sel;
      smtc::CvType cv_type, dcl_cv_type;
      smtc::NamePtr name;
      smtc::ParamPtrVector ctor_param_set;
      bool ctor_vararg = false;
      smtc::ParamPtrVector call_param_set;
      bool call_vararg = false;
      smtc::Cv cv;
      smtc::ThrowSpecPtr throw_spec;
      getNodeFunctorDcl (node.getFunctorDecl (), cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name,
          ctor_param_set, ctor_vararg, call_param_set, call_vararg, cv, throw_spec);
      // base spec set
      smtc::BaseSpecPtrVector base_spec_set;
      getBaseSpecSet (node.getLazyBaseClauseOpt (), base_spec_set);
      smtc::declareFunctor (cs, dcl_spec_sel, dcl_cv_type, name, ctor_param_set, ctor_vararg, call_param_set, call_vararg, cv, throw_spec,
          base_spec_set);
    }
}
namespace
{
  void VisitNode::visit (EnumDefNode & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjNameOpt ());
      smtc::EnumtorPtrVector enumtor_set;
      getEnumtorSet (node.getEnumBodyOpt (), enumtor_set);
      smtc::defineEnum (cs, node.getENUM_TOKEN ().getLoc (), name, enumtor_set);
    }
}
namespace
{
  void VisitNode::visit (UsingDeclNode & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::declareUsing (cs, name);
    }
}
namespace
{
  void VisitNode::visit (UsingDirNode & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::declareUsingDir (cs, name);
    }
}
namespace
{
  void VisitNode::visit (LinkageSpecNode & node) const
    {
      // pop linkage scope
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visit (LinkageBlockBeginNode & node) const
    {
      // create linkage "namespace"
      util::Loc const & loc = node.getEXTERN_TOKEN ().getLoc ();
      util::Ident const & name = node.getLITERAL_STRING_TOKEN ().getLexeme ();
      smtc::ScopePtr res_scope = smtc::openLinkageBlock (cs, loc, name);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (LinkageDeclBeginNode & node) const
    {
      // open linkage spec scope
      util::Loc const & loc = node.getEXTERN_TOKEN ().getLoc ();
      util::Ident const & name = node.getLITERAL_STRING_TOKEN ().getLexeme ();
      smtc::ScopePtr res_scope = smtc::openLinkageSpec (cs, loc, name);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (NavDefNode & node) const
    {
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visit (NavHeadNode & node) const
    {
      SpecSel dcl_spec_sel;
      smtc::CvType ret_type, node_type;
      smtc::NamePtr name;
      smtc::ParamPtrVector param_set;
      getNodeNavDcl (node.getNavDecl (), dcl_spec_sel, ret_type, name, node_type, param_set);
      smtc::BaseSpecPtrVector base_spec_set;
      getBaseSpecSet (node.getLazyBaseClauseOpt (), base_spec_set);
      smtc::ScopePtr res_scope = smtc::defineNavClass (cs, dcl_spec_sel, ret_type, name, node_type, param_set, base_spec_set);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (NavVisitFuncDefNode & node) const
    {
      smtc::NamePtr type_name = getNodeName (node.getObjName1 ());
      smtc::NamePtr param_name = getNodeName (node.getObjName2 ());
      Block body;
      basl::Token block_token = node.getBlockOpt ();
      if (block_token.isSet ())
      {
        body = getBlock (block_token.getLexeme ());
      }
      else
      {
        body = CharBlock (util::Loc ());
      }
      body.setLoc (node.getLBRACE_TOKEN ().getLoc ());
      smtc::defineNavVisitFunc (cs, type_name, param_name, body);
    }
}
namespace
{
  void VisitNode::visit (ReturnStmtNode & node) const
    {
      Block stmt = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      smtc::setReturnStmt (cs, stmt);
    }
}
namespace
{
  void VisitNode::visit (VdfDefNode & node) const
    {
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visit (VdfHeadNode & node) const
    {
      SpecSel decl_spec_sel, dcl_spec_sel;
      smtc::CvType cv_type, dcl_cv_type;
      smtc::NamePtr name;
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      smtc::Cv cv;
      smtc::ThrowSpecPtr throw_spec;
      getNodeFuncDcl (node.getFuncDecl (), cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name, param_set, vararg, cv, throw_spec);
      if (decl_spec_sel.hasSpec (TYPEDEF_SPEC))
      {
        msg::vdfTypedef (decl_spec_sel.getSpecLoc (TYPEDEF_SPEC));
      }
      else if (decl_spec_sel.hasSpec (FRIEND_SPEC))
      {
        msg::vdfFriend (decl_spec_sel.getSpecLoc (FRIEND_SPEC));
      }
      smtc::ScopePtr res_scope = smtc::defineVdf (cs, dcl_spec_sel, dcl_cv_type, name, param_set, vararg, throw_spec);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (VdfFunctorDefNode & node) const
    {
      // name and params
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      getNodeFuncParamBody (node.getParamDecl1Body (), param_set, vararg);
      // body
      Block body;
      basl::Token block_token = node.getBlockOpt ();
      if (block_token.isSet ())
      {
        body = getBlock (block_token.getLexeme ());
      }
      else
      {
        body = CharBlock (util::Loc ());
      }
      body.setLoc (node.getLBRACE_TOKEN ().getLoc ());
      // try block
      smtc::TryBlockPtr try_block;
      visitTryBlock (node.getTryOpt (), node.getHandlerSeqOpt (), try_block);
      smtc::defineVdfFunctor (cs, name, param_set, vararg, body, try_block);
    }
}
namespace
{
  void VisitNode::visit (VdfShortData1DefNode & node) const
    {
      // obj type
      smtc::CvType obj_type;
      getNodeDeclSpec (node.getXUxxDeclSpecSeq (), obj_type);
      // name
      util::Loc const & loc = node.getIDENT_TOKEN ().getLoc ();
      util::Ident const & name = node.getIDENT_TOKEN ().getLexeme ();
      // params
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      visitVdfDataParamList (node.getVdfDataParamListAltOpt (), param_set, vararg);
      // init
      smtc::InitPtr init = getNodeInit (node.getVdfDirectObjInitOpt ());
      smtc::defineVdfShortData (cs, obj_type, loc, name, param_set, vararg, init);
    }
}
namespace
{
  void VisitNode::visit (VdfShortData2DefNode & node) const
    {
      // obj type
      smtc::CvType obj_type;
      getNodeDeclSpec (node.getXUxxDeclSpecSeq (), obj_type);
      // name, remove quotes from name
      util::Loc const & loc = node.getLITERAL_STRING_TOKEN ().getLoc ();
      util::String name = removeQuotes (node.getLITERAL_STRING_TOKEN ().getLexeme ());
      // params
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      visitVdfDataParamList (node.getVdfDataParamListAltOpt (), param_set, vararg);
      // init
      smtc::InitPtr init = getNodeInit (node.getVdfDirectObjInitOpt ());
      smtc::defineVdfShortData (cs, obj_type, loc, name, param_set, vararg, init);
    }
}
namespace
{
  void VisitNode::visit (VdfBlockDataDefNode & node) const
    {
      ss.pop_back ();
    }
}
namespace
{
  void VisitNode::visit (VdfBlockDataHead1Node & node) const
    {
      // name
      util::Loc const & loc = node.getIDENT_TOKEN ().getLoc ();
      util::Ident const & name = node.getIDENT_TOKEN ().getLexeme ();
      // params
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      visitVdfDataParamList (node.getVdfDataParamListAltOpt (), param_set, vararg);
      smtc::ScopePtr res_scope = smtc::defineVdfBlockData (cs, loc, name, param_set, vararg);
      ss.push_back (res_scope);
    }
}
namespace
{
  void VisitNode::visit (VdfBlockDataHead2Node & node) const
    {
      // name, remove quotes from name
      util::Loc const & loc = node.getLITERAL_STRING_TOKEN ().getLoc ();
      util::String name = removeQuotes (node.getLITERAL_STRING_TOKEN ().getLexeme ());
      // params
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      visitVdfDataParamList (node.getVdfDataParamListAltOpt (), param_set, vararg);
      smtc::ScopePtr res_scope = smtc::defineVdfBlockData (cs, loc, name, param_set, vararg);
      ss.push_back (res_scope);
    }
}
namespace
{
  LZZ_INLINE VisitNode::VisitNode (smtc::ScopePtrDeque & ss, smtc::ScopePtr const & cs)
    : Visitor (false), ss (ss), cs (cs)
         {}
}
namespace
{
  VisitNode::~ VisitNode ()
         {}
}
namespace gram
{
  void visitNode (basl::Nonterm & nonterm, smtc::ScopePtrDeque & ss)
  {
    nonterm.accept (VisitNode (ss, ss.back ()));
  }
}
#undef LZZ_INLINE
