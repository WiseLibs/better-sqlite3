// gram_DeclareNodeSimpleDecl.cpp
//

#include "gram_DeclareNodeSimpleDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_DeclareNodeSimpleDecl.inl"
#endif
// gram
#include "gram_DeclSpecFlags.h"
#include "gram_GetNodeDcl.h"
#include "gram_GetNodeInit.h"
#include "gram_Message.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_DeclareFunc.h"
#include "smtc_DeclareObj.h"
#include "smtc_DeclareTdef.h"
#include "smtc_GetFuncType.h"
#include "smtc_GetNameLoc.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct DeclareNodeSimpleDecl : Visitor
  {
    smtc::ScopePtr const & cs;
    SpecSel & decl_spec_sel;
    SpecSel & dcl_spec_sel;
    smtc::CvType & cv_type;
    void visit (NestedSimpleDecl1Node & node) const;
    void visit (NestedSimpleDecl2Node & node) const;
    void visit (NestedSimpleDecl3Node & node) const;
  public:
    explicit DeclareNodeSimpleDecl (smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type);
    ~ DeclareNodeSimpleDecl ();
  };
}
namespace
{
  void DeclareNodeSimpleDecl::visit (NestedSimpleDecl1Node & node) const
    {
      smtc::CvType dcl_cv_type;
      smtc::NamePtr name;
      getNodeObjDcl (node.getNestedObjDecl (), cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name);
      smtc::InitPtr init;
      basl::Nonterm obj_init = node.getObjInitOpt ();
      if (obj_init.isSet ())
      {
        init = getNodeInit (obj_init); 
      }
      if (decl_spec_sel.hasSpec (TYPEDEF_SPEC))
      {
        smtc::declareTdef (cs, dcl_cv_type, name);
      }
      // friend not allowed by grammar
      else
      {
        smtc::declareObj (cs, dcl_spec_sel, dcl_cv_type, name, init);
      }
    }
}
namespace
{
  void DeclareNodeSimpleDecl::visit (NestedSimpleDecl2Node & node) const
    {
      smtc::CvType dcl_cv_type;
      smtc::NamePtr name;
      smtc::ParamPtrVector param_set;
      bool vararg = false;
      smtc::Cv cv;
      smtc::ThrowSpecPtr throw_spec;
      getNodeFuncDcl (node.getNestedFuncDecl (), cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name,
          param_set, vararg, cv, throw_spec);
      if (decl_spec_sel.hasSpec (TYPEDEF_SPEC))
      {
        dcl_cv_type = smtc::getFuncType (dcl_cv_type, param_set, vararg, cv, throw_spec);
        smtc::declareTdef (cs, dcl_cv_type, name);
      }
      else if (decl_spec_sel.hasSpec (FRIEND_SPEC))
      {
        smtc::declareFrndFunc (cs, dcl_spec_sel, dcl_cv_type, name, param_set, vararg, cv, throw_spec);
      }
      else
      {
        smtc::declareFunc (cs, dcl_spec_sel, dcl_cv_type, name, param_set, vararg, cv, throw_spec);
      }
    }
}
namespace
{
  void DeclareNodeSimpleDecl::visit (NestedSimpleDecl3Node & node) const
    {
      smtc::CvType dcl_cv_type;
      smtc::NamePtr name;
      getNodeObjDcl (node.getNestedBitfDecl (), cs, decl_spec_sel, dcl_spec_sel, cv_type, dcl_cv_type, name);
      if (decl_spec_sel.hasSpec (TYPEDEF_SPEC))
      {
        msg::bitfieldTdef (smtc::getNameLoc (name));
      }
      // friend not allowed by grammar
      else
      {
        smtc::declareObj (cs, dcl_spec_sel, dcl_cv_type, name, smtc::InitPtr ());
      }
    }
}
namespace
{
  LZZ_INLINE DeclareNodeSimpleDecl::DeclareNodeSimpleDecl (smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type)
    : cs (cs), decl_spec_sel (decl_spec_sel), dcl_spec_sel (dcl_spec_sel), cv_type (cv_type)
         {}
}
namespace
{
  DeclareNodeSimpleDecl::~ DeclareNodeSimpleDecl ()
         {}
}
namespace gram
{
  void declareNodeSimpleDecl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type)
  {
    nonterm.accept (DeclareNodeSimpleDecl (cs, decl_spec_sel, dcl_spec_sel, cv_type));
  }
}
#undef LZZ_INLINE
