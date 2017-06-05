// gram_Visitor.h
//

#ifndef LZZ_gram_Visitor_h
#define LZZ_gram_Visitor_h
#include "basl_Visitor.h"
#define LZZ_INLINE inline
namespace gram
{
  class SimpleDeclNode;
}
namespace gram
{
  class NestedSimpleDecl1Node;
}
namespace gram
{
  class NestedSimpleDecl2Node;
}
namespace gram
{
  class NestedSimpleDecl3Node;
}
namespace gram
{
  class NestedDeclNode;
}
namespace gram
{
  class ObjInit1Node;
}
namespace gram
{
  class ObjInit2Node;
}
namespace gram
{
  class ObjInit3Node;
}
namespace gram
{
  class BlockNode;
}
namespace gram
{
  class NestedName1Node;
}
namespace gram
{
  class NestedName2Node;
}
namespace gram
{
  class Name1Node;
}
namespace gram
{
  class Name2Node;
}
namespace gram
{
  class Name3Node;
}
namespace gram
{
  class BaseName1Node;
}
namespace gram
{
  class Name4Node;
}
namespace gram
{
  class Name5Node;
}
namespace gram
{
  class BaseName2Node;
}
namespace gram
{
  class BaseName3Node;
}
namespace gram
{
  class BaseName4Node;
}
namespace gram
{
  class Oper1Node;
}
namespace gram
{
  class Oper2Node;
}
namespace gram
{
  class Oper3Node;
}
namespace gram
{
  class Oper4Node;
}
namespace gram
{
  class Oper5Node;
}
namespace gram
{
  class DeclSpecNode;
}
namespace gram
{
  class CVSpecNode;
}
namespace gram
{
  class SeqNode;
}
namespace gram
{
  class FtorSpecNode;
}
namespace gram
{
  class UserTypeNode;
}
namespace gram
{
  class ElabTypeNode;
}
namespace gram
{
  class BuiltInTypeNode;
}
namespace gram
{
  class DclNode;
}
namespace gram
{
  class DirectDcl1Node;
}
namespace gram
{
  class DirectDcl2Node;
}
namespace gram
{
  class DirectDcl3Node;
}
namespace gram
{
  class PureDclNode;
}
namespace gram
{
  class PureNode;
}
namespace gram
{
  class DirectDcl4Node;
}
namespace gram
{
  class PtrOper1Node;
}
namespace gram
{
  class PtrOper2Node;
}
namespace gram
{
  class PtrOper3Node;
}
namespace gram
{
  class IdNode;
}
namespace gram
{
  class ParamDeclBody1Node;
}
namespace gram
{
  class ParamDeclBody2Node;
}
namespace gram
{
  class ParamDeclBody3Node;
}
namespace gram
{
  class ParamDeclBody4Node;
}
namespace gram
{
  class ParamDecl1Node;
}
namespace gram
{
  class ParamDecl2Node;
}
namespace gram
{
  class Decl2Node;
}
namespace gram
{
  class Decl1Node;
}
namespace gram
{
  class TypeIdNode;
}
namespace gram
{
  class NamespaceDefNode;
}
namespace gram
{
  class NamespaceHead1Node;
}
namespace gram
{
  class NamespaceHead2Node;
}
namespace gram
{
  class ClassDefNode;
}
namespace gram
{
  class ClassHeadNode;
}
namespace gram
{
  class BaseSpec1Node;
}
namespace gram
{
  class BaseSpec2Node;
}
namespace gram
{
  class BaseSpec3Node;
}
namespace gram
{
  class AccessSpecNode;
}
namespace gram
{
  class ClassDeclNode;
}
namespace gram
{
  class FriendClassDeclNode;
}
namespace gram
{
  class FuncDefNode;
}
namespace gram
{
  class MbrInitNode;
}
namespace gram
{
  class HandlerNode;
}
namespace gram
{
  class TmplDeclNode;
}
namespace gram
{
  class TmplSpecNode;
}
namespace gram
{
  class TypeParam1Node;
}
namespace gram
{
  class TypeParam2Node;
}
namespace gram
{
  class TmplTmplParam1Node;
}
namespace gram
{
  class TmplTmplParam2Node;
}
namespace gram
{
  class TmplInstNode;
}
namespace gram
{
  class TmplInstBeginNode;
}
namespace gram
{
  class LazyCtorNode;
}
namespace gram
{
  class LazyCtorBegin1Node;
}
namespace gram
{
  class LazyCtorBegin2Node;
}
namespace gram
{
  class LazyBaseSpec1Node;
}
namespace gram
{
  class LazyBaseSpec2Node;
}
namespace gram
{
  class LazyBaseSpec3Node;
}
namespace gram
{
  class DirectDcl5Node;
}
namespace gram
{
  class FunctorDefNode;
}
namespace gram
{
  class FunctorDeclTypeNode;
}
namespace gram
{
  class EnumDefNode;
}
namespace gram
{
  class EnumtorDecl1Node;
}
namespace gram
{
  class EnumtorDecl2Node;
}
namespace gram
{
  class UsingDeclNode;
}
namespace gram
{
  class UsingDirNode;
}
namespace gram
{
  class LinkageSpecNode;
}
namespace gram
{
  class LinkageBlockBeginNode;
}
namespace gram
{
  class LinkageDeclBeginNode;
}
namespace gram
{
  class NavDefNode;
}
namespace gram
{
  class NavHeadNode;
}
namespace gram
{
  class NavDirectDcl1Node;
}
namespace gram
{
  class NavVisitFuncDefNode;
}
namespace gram
{
  class ReturnStmtNode;
}
namespace gram
{
  class VdfDefNode;
}
namespace gram
{
  class VdfHeadNode;
}
namespace gram
{
  class VdfFunctorDefNode;
}
namespace gram
{
  class VdfShortData1DefNode;
}
namespace gram
{
  class VdfShortData2DefNode;
}
namespace gram
{
  class VdfDataParamListNode;
}
namespace gram
{
  class ObjInit4Node;
}
namespace gram
{
  class VdfBlockDataDefNode;
}
namespace gram
{
  class VdfBlockDataHead1Node;
}
namespace gram
{
  class VdfBlockDataHead2Node;
}
namespace gram
{
  class DirectDcl6Node;
}
namespace gram
{
  class Visitor : public basl::Visitor
  {
    bool m_slippery;
  public:
    Visitor (bool slippery = true);
    virtual void visit (gram::SimpleDeclNode & node) const;
    virtual void visit (gram::NestedSimpleDecl1Node & node) const;
    virtual void visit (gram::NestedSimpleDecl2Node & node) const;
    virtual void visit (gram::NestedSimpleDecl3Node & node) const;
    virtual void visit (gram::NestedDeclNode & node) const;
    virtual void visit (gram::ObjInit1Node & node) const;
    virtual void visit (gram::ObjInit2Node & node) const;
    virtual void visit (gram::ObjInit3Node & node) const;
    virtual void visit (gram::BlockNode & node) const;
    virtual void visit (gram::NestedName1Node & node) const;
    virtual void visit (gram::NestedName2Node & node) const;
    virtual void visit (gram::Name1Node & node) const;
    virtual void visit (gram::Name2Node & node) const;
    virtual void visit (gram::Name3Node & node) const;
    virtual void visit (gram::BaseName1Node & node) const;
    virtual void visit (gram::Name4Node & node) const;
    virtual void visit (gram::Name5Node & node) const;
    virtual void visit (gram::BaseName2Node & node) const;
    virtual void visit (gram::BaseName3Node & node) const;
    virtual void visit (gram::BaseName4Node & node) const;
    virtual void visit (gram::Oper1Node & node) const;
    virtual void visit (gram::Oper2Node & node) const;
    virtual void visit (gram::Oper3Node & node) const;
    virtual void visit (gram::Oper4Node & node) const;
    virtual void visit (gram::Oper5Node & node) const;
    virtual void visit (gram::DeclSpecNode & node) const;
    virtual void visit (gram::CVSpecNode & node) const;
    virtual void visit (gram::SeqNode & node) const;
    virtual void visit (gram::FtorSpecNode & node) const;
    virtual void visit (gram::UserTypeNode & node) const;
    virtual void visit (gram::ElabTypeNode & node) const;
    virtual void visit (gram::BuiltInTypeNode & node) const;
    virtual void visit (gram::DclNode & node) const;
    virtual void visit (gram::DirectDcl1Node & node) const;
    virtual void visit (gram::DirectDcl2Node & node) const;
    virtual void visit (gram::DirectDcl3Node & node) const;
    virtual void visit (gram::PureDclNode & node) const;
    virtual void visit (gram::PureNode & node) const;
    virtual void visit (gram::DirectDcl4Node & node) const;
    virtual void visit (gram::PtrOper1Node & node) const;
    virtual void visit (gram::PtrOper2Node & node) const;
    virtual void visit (gram::PtrOper3Node & node) const;
    virtual void visit (gram::IdNode & node) const;
    virtual void visit (gram::ParamDeclBody1Node & node) const;
    virtual void visit (gram::ParamDeclBody2Node & node) const;
    virtual void visit (gram::ParamDeclBody3Node & node) const;
    virtual void visit (gram::ParamDeclBody4Node & node) const;
    virtual void visit (gram::ParamDecl1Node & node) const;
    virtual void visit (gram::ParamDecl2Node & node) const;
    virtual void visit (gram::Decl2Node & node) const;
    virtual void visit (gram::Decl1Node & node) const;
    virtual void visit (gram::TypeIdNode & node) const;
    virtual void visit (gram::NamespaceDefNode & node) const;
    virtual void visit (gram::NamespaceHead1Node & node) const;
    virtual void visit (gram::NamespaceHead2Node & node) const;
    virtual void visit (gram::ClassDefNode & node) const;
    virtual void visit (gram::ClassHeadNode & node) const;
    virtual void visit (gram::BaseSpec1Node & node) const;
    virtual void visit (gram::BaseSpec2Node & node) const;
    virtual void visit (gram::BaseSpec3Node & node) const;
    virtual void visit (gram::AccessSpecNode & node) const;
    virtual void visit (gram::ClassDeclNode & node) const;
    virtual void visit (gram::FriendClassDeclNode & node) const;
    virtual void visit (gram::FuncDefNode & node) const;
    virtual void visit (gram::MbrInitNode & node) const;
    virtual void visit (gram::HandlerNode & node) const;
    virtual void visit (gram::TmplDeclNode & node) const;
    virtual void visit (gram::TmplSpecNode & node) const;
    virtual void visit (gram::TypeParam1Node & node) const;
    virtual void visit (gram::TypeParam2Node & node) const;
    virtual void visit (gram::TmplTmplParam1Node & node) const;
    virtual void visit (gram::TmplTmplParam2Node & node) const;
    virtual void visit (gram::TmplInstNode & node) const;
    virtual void visit (gram::TmplInstBeginNode & node) const;
    virtual void visit (gram::LazyCtorNode & node) const;
    virtual void visit (gram::LazyCtorBegin1Node & node) const;
    virtual void visit (gram::LazyCtorBegin2Node & node) const;
    virtual void visit (gram::LazyBaseSpec1Node & node) const;
    virtual void visit (gram::LazyBaseSpec2Node & node) const;
    virtual void visit (gram::LazyBaseSpec3Node & node) const;
    virtual void visit (gram::DirectDcl5Node & node) const;
    virtual void visit (gram::FunctorDefNode & node) const;
    virtual void visit (gram::FunctorDeclTypeNode & node) const;
    virtual void visit (gram::EnumDefNode & node) const;
    virtual void visit (gram::EnumtorDecl1Node & node) const;
    virtual void visit (gram::EnumtorDecl2Node & node) const;
    virtual void visit (gram::UsingDeclNode & node) const;
    virtual void visit (gram::UsingDirNode & node) const;
    virtual void visit (gram::LinkageSpecNode & node) const;
    virtual void visit (gram::LinkageBlockBeginNode & node) const;
    virtual void visit (gram::LinkageDeclBeginNode & node) const;
    virtual void visit (gram::NavDefNode & node) const;
    virtual void visit (gram::NavHeadNode & node) const;
    virtual void visit (gram::NavDirectDcl1Node & node) const;
    virtual void visit (gram::NavVisitFuncDefNode & node) const;
    virtual void visit (gram::ReturnStmtNode & node) const;
    virtual void visit (gram::VdfDefNode & node) const;
    virtual void visit (gram::VdfHeadNode & node) const;
    virtual void visit (gram::VdfFunctorDefNode & node) const;
    virtual void visit (gram::VdfShortData1DefNode & node) const;
    virtual void visit (gram::VdfShortData2DefNode & node) const;
    virtual void visit (gram::VdfDataParamListNode & node) const;
    virtual void visit (gram::ObjInit4Node & node) const;
    virtual void visit (gram::VdfBlockDataDefNode & node) const;
    virtual void visit (gram::VdfBlockDataHead1Node & node) const;
    virtual void visit (gram::VdfBlockDataHead2Node & node) const;
    virtual void visit (gram::DirectDcl6Node & node) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_Visitor.inl"
#endif
#endif
