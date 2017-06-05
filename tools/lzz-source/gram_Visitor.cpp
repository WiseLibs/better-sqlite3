// gram_Visitor.cpp
//

#include "gram_Visitor.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_Visitor.inl"
#endif
#include "gram_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  void Visitor::visit (gram::SimpleDeclNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NestedSimpleDecl1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NestedSimpleDecl2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NestedSimpleDecl3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NestedDeclNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ObjInit1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ObjInit2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ObjInit3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BlockNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NestedName1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NestedName2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Name1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Name2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Name3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BaseName1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Name4Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Name5Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BaseName2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BaseName3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BaseName4Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Oper1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Oper2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Oper3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Oper4Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Oper5Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::DeclSpecNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::CVSpecNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::SeqNode & node) const
    {
      if (m_slippery)
      {
        node.visitChildren (* this);
      }
    }
}
namespace gram
{
  void Visitor::visit (gram::FtorSpecNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::UserTypeNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ElabTypeNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BuiltInTypeNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::DclNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::DirectDcl1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::DirectDcl2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::DirectDcl3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::PureDclNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::PureNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::DirectDcl4Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::PtrOper1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::PtrOper2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::PtrOper3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::IdNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ParamDeclBody1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ParamDeclBody2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ParamDeclBody3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ParamDeclBody4Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ParamDecl1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ParamDecl2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Decl2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::Decl1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TypeIdNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NamespaceDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NamespaceHead1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NamespaceHead2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ClassDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ClassHeadNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BaseSpec1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BaseSpec2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::BaseSpec3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::AccessSpecNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ClassDeclNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::FriendClassDeclNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::FuncDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::MbrInitNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::HandlerNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TmplDeclNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TmplSpecNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TypeParam1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TypeParam2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TmplTmplParam1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TmplTmplParam2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TmplInstNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::TmplInstBeginNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LazyCtorNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LazyCtorBegin1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LazyCtorBegin2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LazyBaseSpec1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LazyBaseSpec2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LazyBaseSpec3Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::DirectDcl5Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::FunctorDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::FunctorDeclTypeNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::EnumDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::EnumtorDecl1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::EnumtorDecl2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::UsingDeclNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::UsingDirNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LinkageSpecNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LinkageBlockBeginNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::LinkageDeclBeginNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NavDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NavHeadNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NavDirectDcl1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::NavVisitFuncDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ReturnStmtNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfHeadNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfFunctorDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfShortData1DefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfShortData2DefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfDataParamListNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::ObjInit4Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfBlockDataDefNode & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfBlockDataHead1Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::VdfBlockDataHead2Node & node) const
    {}
}
namespace gram
{
  void Visitor::visit (gram::DirectDcl6Node & node) const
    {}
}
#undef LZZ_INLINE
