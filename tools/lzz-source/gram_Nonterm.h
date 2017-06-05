// gram_Nonterm.h
//

#ifndef LZZ_gram_Nonterm_h
#define LZZ_gram_Nonterm_h
#include "basl_NontermProxy.h"
#define LZZ_INLINE inline
namespace gram
{
  class SimpleDeclNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    SimpleDeclNode (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedSimpleDecl () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class NestedSimpleDecl1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NestedSimpleDecl1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedObjDecl () const;
    basl::Nonterm & getObjInitOpt () const;
  };
}
namespace gram
{
  class NestedSimpleDecl2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NestedSimpleDecl2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedFuncDecl () const;
  };
}
namespace gram
{
  class NestedSimpleDecl3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NestedSimpleDecl3Node (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedBitfDecl () const;
  };
}
namespace gram
{
  class NestedDeclNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NestedDeclNode (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedSimpleDecl () const;
    basl::Token & getCOMMA_TOKEN () const;
    basl::Nonterm & getObjDcl () const;
  };
}
namespace gram
{
  class ObjInit1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ObjInit1Node (basl::Nonterm & nonterm);
    basl::Token & getASSIGN_TOKEN () const;
    basl::Token & getBLOCK_TOKEN () const;
  };
}
namespace gram
{
  class ObjInit2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ObjInit2Node (basl::Nonterm & nonterm);
    basl::Token & getDINIT_TOKEN () const;
    basl::Token & getLPAREN_TOKEN () const;
    basl::Nonterm & getExprList () const;
    basl::Token & getRPAREN_TOKEN () const;
  };
}
namespace gram
{
  class ObjInit3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ObjInit3Node (basl::Nonterm & nonterm);
    basl::Nonterm & getDirectExprList () const;
    basl::Token & getRPAREN_TOKEN () const;
  };
}
namespace gram
{
  class BlockNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BlockNode (basl::Nonterm & nonterm);
    basl::Token & getBLOCK_TOKEN () const;
  };
}
namespace gram
{
  class NestedName1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NestedName1Node (basl::Nonterm & nonterm);
    basl::Token & getDCOLON_TOKEN () const;
  };
}
namespace gram
{
  class NestedName2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NestedName2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
    basl::Token & getDCOLON_TOKEN () const;
  };
}
namespace gram
{
  class Name1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Name1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedNameOpt () const;
    basl::Nonterm & getObjBaseName () const;
  };
}
namespace gram
{
  class Name2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Name2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedNameOpt () const;
    basl::Nonterm & getObjBaseName () const;
    basl::Token & getLT_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getGT_TOKEN () const;
  };
}
namespace gram
{
  class Name3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Name3Node (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedName () const;
    basl::Token & getTEMPLATE_TOKEN () const;
    basl::Nonterm & getObjBaseName () const;
    basl::Token & getLT_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getGT_TOKEN () const;
  };
}
namespace gram
{
  class BaseName1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BaseName1Node (basl::Nonterm & nonterm);
    basl::Token & getMacroOpt () const;
    basl::Token & getIDENT_TOKEN () const;
  };
}
namespace gram
{
  class Name4Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Name4Node (basl::Nonterm & nonterm);
    basl::Nonterm & getNestedNameOpt () const;
    basl::Token & getMacroOpt () const;
    basl::Token & getIDENT_TOKEN () const;
    basl::Token & getCOLON_TOKEN () const;
    basl::Token & getBLOCK_TOKEN () const;
  };
}
namespace gram
{
  class Name5Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Name5Node (basl::Nonterm & nonterm);
    basl::Token & getCOLON_TOKEN () const;
    basl::Token & getBLOCK_TOKEN () const;
  };
}
namespace gram
{
  class BaseName2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BaseName2Node (basl::Nonterm & nonterm);
    basl::Token & getMacroOpt () const;
    basl::Token & getBITNOT_TOKEN () const;
    basl::Token & getIDENT_TOKEN () const;
  };
}
namespace gram
{
  class BaseName3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BaseName3Node (basl::Nonterm & nonterm);
    basl::Token & getMacroOpt () const;
    basl::Token & getOPERATOR_TOKEN () const;
    basl::Nonterm & getOper () const;
  };
}
namespace gram
{
  class BaseName4Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BaseName4Node (basl::Nonterm & nonterm);
    basl::Token & getMacroOpt () const;
    basl::Token & getOPERATOR_TOKEN () const;
    basl::Nonterm & getAbstractDecl () const;
  };
}
namespace gram
{
  class Oper1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Oper1Node (basl::Nonterm & nonterm);
    basl::Token & getLPAREN_TOKEN () const;
    basl::Token & getRPAREN_TOKEN () const;
  };
}
namespace gram
{
  class Oper2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Oper2Node (basl::Nonterm & nonterm);
    basl::Token & getLBRACK_TOKEN () const;
    basl::Token & getRBRACK_TOKEN () const;
  };
}
namespace gram
{
  class Oper3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Oper3Node (basl::Nonterm & nonterm);
    basl::Token & getNEW_TOKEN () const;
    basl::Token & getLBRACK_TOKEN () const;
    basl::Token & getRBRACK_TOKEN () const;
  };
}
namespace gram
{
  class Oper4Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Oper4Node (basl::Nonterm & nonterm);
    basl::Token & getDELETE_TOKEN () const;
    basl::Token & getLBRACK_TOKEN () const;
    basl::Token & getRBRACK_TOKEN () const;
  };
}
namespace gram
{
  class Oper5Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Oper5Node (basl::Nonterm & nonterm);
    basl::Token & getSingleOper () const;
  };
}
namespace gram
{
  class DeclSpecNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    DeclSpecNode (basl::Nonterm & nonterm);
    basl::Token & getTYPEDEF_TOKEN () const;
  };
}
namespace gram
{
  class CVSpecNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    CVSpecNode (basl::Nonterm & nonterm);
    basl::Token & getCvToken () const;
  };
}
namespace gram
{
  class SeqNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    SeqNode (basl::Nonterm & nonterm);
    basl::Nonterm & getCvSpecSeq () const;
    basl::Nonterm & getCvSpec () const;
  };
}
namespace gram
{
  class FtorSpecNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    FtorSpecNode (basl::Nonterm & nonterm);
    basl::Token & getFtorToken () const;
  };
}
namespace gram
{
  class UserTypeNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    UserTypeNode (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class ElabTypeNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ElabTypeNode (basl::Nonterm & nonterm);
    basl::Token & getClassKey () const;
    basl::Token & getDllApiOpt () const;
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class BuiltInTypeNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BuiltInTypeNode (basl::Nonterm & nonterm);
    basl::Token & getBuiltInTypeToken () const;
  };
}
namespace gram
{
  class DclNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    DclNode (basl::Nonterm & nonterm);
    basl::Nonterm & getPtrOper () const;
    basl::Nonterm & getObjADcl () const;
  };
}
namespace gram
{
  class DirectDcl1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    DirectDcl1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjBDirectDcl () const;
    basl::Nonterm & getParamDecl1Body () const;
    basl::Token & getRPAREN_TOKEN () const;
    basl::Nonterm & getCvSpecSeqOpt () const;
    basl::Nonterm & getThrowSpecOpt () const;
  };
}
namespace gram
{
  class DirectDcl2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    DirectDcl2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjADirectDcl () const;
    basl::Token & getLBRACK_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getRBRACK_TOKEN () const;
  };
}
namespace gram
{
  class DirectDcl3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    DirectDcl3Node (basl::Nonterm & nonterm);
    basl::Token & getLPAREN_TOKEN () const;
    basl::Nonterm & getObjBDcl () const;
    basl::Token & getRPAREN_TOKEN () const;
  };
}
namespace gram
{
  class PureDclNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    PureDclNode (basl::Nonterm & nonterm);
    basl::Nonterm & getFuncDcl () const;
    basl::Nonterm & getPureOpt () const;
  };
}
namespace gram
{
  class PureNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    PureNode (basl::Nonterm & nonterm);
    basl::Token & getASSIGN_TOKEN () const;
    basl::Token & getZERO_TOKEN () const;
  };
}
namespace gram
{
  class DirectDcl4Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    DirectDcl4Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjDclId () const;
    basl::Nonterm & getParamDecl1Body () const;
    basl::Token & getRPAREN_TOKEN () const;
    basl::Nonterm & getCvSpecSeqOpt () const;
    basl::Nonterm & getThrowSpecOpt () const;
  };
}
namespace gram
{
  class PtrOper1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    PtrOper1Node (basl::Nonterm & nonterm);
    basl::Token & getTIMES_TOKEN () const;
    basl::Nonterm & getCvSpecSeqOpt () const;
  };
}
namespace gram
{
  class PtrOper2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    PtrOper2Node (basl::Nonterm & nonterm);
    basl::Token & getBITAND_TOKEN () const;
  };
}
namespace gram
{
  class PtrOper3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    PtrOper3Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
    basl::Token & getDCOLON_TOKEN () const;
    basl::Token & getTIMES_TOKEN () const;
    basl::Nonterm & getCvSpecSeqOpt () const;
  };
}
namespace gram
{
  class IdNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    IdNode (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class ParamDeclBody1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ParamDeclBody1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getParamDecl1List () const;
    basl::Token & getEllipseOpt () const;
  };
}
namespace gram
{
  class ParamDeclBody2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ParamDeclBody2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getParamDecl1List () const;
    basl::Token & getCOMMA_TOKEN () const;
    basl::Token & getELLIPSE_TOKEN () const;
  };
}
namespace gram
{
  class ParamDeclBody3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ParamDeclBody3Node (basl::Nonterm & nonterm);
    basl::Token & getLPAREN_TOKEN () const;
    basl::Token & getEllipseOpt () const;
  };
}
namespace gram
{
  class ParamDeclBody4Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ParamDeclBody4Node (basl::Nonterm & nonterm);
    basl::Token & getLPAREN_TOKEN () const;
    basl::Token & getVOID_TOKEN () const;
  };
}
namespace gram
{
  class ParamDecl1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ParamDecl1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getParamDecl () const;
  };
}
namespace gram
{
  class ParamDecl2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ParamDecl2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getParamDecl () const;
    basl::Token & getASSIGN_TOKEN () const;
    basl::Token & getBLOCK_TOKEN () const;
  };
}
namespace gram
{
  class Decl2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Decl2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getXBxxDeclSpecSeq () const;
    basl::Nonterm & getObjDcl () const;
  };
}
namespace gram
{
  class Decl1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    Decl1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getPureCtorDcl () const;
  };
}
namespace gram
{
  class TypeIdNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TypeIdNode (basl::Nonterm & nonterm);
    basl::Nonterm & getAbstractDecl () const;
  };
}
namespace gram
{
  class NamespaceDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NamespaceDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getNamespaceHead () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Nonterm & getDeclSeqOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
  };
}
namespace gram
{
  class NamespaceHead1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NamespaceHead1Node (basl::Nonterm & nonterm);
    basl::Token & getNAMESPACE_TOKEN () const;
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class NamespaceHead2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NamespaceHead2Node (basl::Nonterm & nonterm);
    basl::Token & getNAMESPACE_TOKEN () const;
  };
}
namespace gram
{
  class ClassDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ClassDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getClassHead () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Nonterm & getMbrDeclSeqOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
    basl::Token & getSemiOpt () const;
  };
}
namespace gram
{
  class ClassHeadNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ClassHeadNode (basl::Nonterm & nonterm);
    basl::Token & getClassKey () const;
    basl::Token & getDllApiOpt () const;
    basl::Nonterm & getObjName () const;
    basl::Nonterm & getBaseClauseOpt () const;
  };
}
namespace gram
{
  class BaseSpec1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BaseSpec1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class BaseSpec2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BaseSpec2Node (basl::Nonterm & nonterm);
    basl::Token & getVIRTUAL_TOKEN () const;
    basl::Token & getAccessOpt () const;
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class BaseSpec3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    BaseSpec3Node (basl::Nonterm & nonterm);
    basl::Token & getAccess () const;
    basl::Token & getVirtualOpt () const;
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class AccessSpecNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    AccessSpecNode (basl::Nonterm & nonterm);
    basl::Token & getAccess () const;
    basl::Token & getCOLON_TOKEN () const;
  };
}
namespace gram
{
  class ClassDeclNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ClassDeclNode (basl::Nonterm & nonterm);
    basl::Nonterm & getXExxDeclSpecSeq () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class FriendClassDeclNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    FriendClassDeclNode (basl::Nonterm & nonterm);
    basl::Nonterm & getFExxDeclSpecSeq () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class FuncDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    FuncDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getFuncDecl () const;
    basl::Token & getTryOpt () const;
    basl::Nonterm & getCtorInitOpt () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
    basl::Nonterm & getHandlerSeqOpt () const;
  };
}
namespace gram
{
  class MbrInitNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    MbrInitNode (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
    basl::Token & getLPAREN_TOKEN () const;
    basl::Nonterm & getExprListOpt () const;
    basl::Token & getRPAREN_TOKEN () const;
  };
}
namespace gram
{
  class HandlerNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    HandlerNode (basl::Nonterm & nonterm);
    basl::Token & getCATCH_TOKEN () const;
    basl::Token & getLPAREN_TOKEN () const;
    basl::Nonterm & getCatchDecl () const;
    basl::Token & getRPAREN_TOKEN () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
  };
}
namespace gram
{
  class TmplDeclNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TmplDeclNode (basl::Nonterm & nonterm);
    basl::Nonterm & getTmplSpec () const;
    basl::Nonterm & getTmplSpecDecl () const;
  };
}
namespace gram
{
  class TmplSpecNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TmplSpecNode (basl::Nonterm & nonterm);
    basl::Token & getTEMPLATE_TOKEN () const;
    basl::Token & getLT_TOKEN () const;
    basl::Nonterm & getTmplParamListOpt () const;
    basl::Token & getGT_TOKEN () const;
  };
}
namespace gram
{
  class TypeParam1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TypeParam1Node (basl::Nonterm & nonterm);
    basl::Token & getTypeKey () const;
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class TypeParam2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TypeParam2Node (basl::Nonterm & nonterm);
    basl::Token & getTypeKey () const;
    basl::Nonterm & getObjName () const;
    basl::Token & getASSIGN_TOKEN () const;
    basl::Nonterm & getAbstractDecl () const;
  };
}
namespace gram
{
  class TmplTmplParam1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TmplTmplParam1Node (basl::Nonterm & nonterm);
    basl::Token & getTEMPLATE_TOKEN () const;
    basl::Token & getLT_TOKEN () const;
    basl::Nonterm & getTmplParamListOpt () const;
    basl::Token & getGT_TOKEN () const;
    basl::Token & getCLASS_TOKEN () const;
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class TmplTmplParam2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TmplTmplParam2Node (basl::Nonterm & nonterm);
    basl::Token & getTEMPLATE_TOKEN () const;
    basl::Token & getLT_TOKEN () const;
    basl::Nonterm & getTmplParamListOpt () const;
    basl::Token & getGT_TOKEN () const;
    basl::Token & getCLASS_TOKEN () const;
    basl::Nonterm & getObjName1 () const;
    basl::Token & getASSIGN_TOKEN () const;
    basl::Nonterm & getObjName2 () const;
  };
}
namespace gram
{
  class TmplInstNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TmplInstNode (basl::Nonterm & nonterm);
    basl::Nonterm & getTmplInstBegin () const;
    basl::Nonterm & getTmplInstDecl () const;
  };
}
namespace gram
{
  class TmplInstBeginNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    TmplInstBeginNode (basl::Nonterm & nonterm);
    basl::Token & getTEMPLATE_TOKEN () const;
  };
}
namespace gram
{
  class LazyCtorNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LazyCtorNode (basl::Nonterm & nonterm);
    basl::Nonterm & getLazyCtorBegin () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Nonterm & getMbrDeclSeqOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
    basl::Token & getSemiOpt () const;
  };
}
namespace gram
{
  class LazyCtorBegin1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LazyCtorBegin1Node (basl::Nonterm & nonterm);
    basl::Token & getClassKey () const;
    basl::Token & getDllApiOpt () const;
    basl::Nonterm & getObjName () const;
    basl::Nonterm & getParamDecl1Body () const;
    basl::Token & getRPAREN_TOKEN () const;
    basl::Nonterm & getLazyBaseClauseOpt () const;
  };
}
namespace gram
{
  class LazyCtorBegin2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LazyCtorBegin2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getXxxSDeclSpecSeq () const;
    basl::Token & getClassKey () const;
    basl::Token & getDllApiOpt () const;
    basl::Nonterm & getObjName () const;
    basl::Nonterm & getParamDecl1Body () const;
    basl::Token & getRPAREN_TOKEN () const;
    basl::Nonterm & getLazyBaseClauseOpt () const;
  };
}
namespace gram
{
  class LazyBaseSpec1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LazyBaseSpec1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
    basl::Nonterm & getBaseInit () const;
  };
}
namespace gram
{
  class LazyBaseSpec2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LazyBaseSpec2Node (basl::Nonterm & nonterm);
    basl::Token & getVIRTUAL_TOKEN () const;
    basl::Token & getAccessOpt () const;
    basl::Nonterm & getObjName () const;
    basl::Nonterm & getBaseInit () const;
  };
}
namespace gram
{
  class LazyBaseSpec3Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LazyBaseSpec3Node (basl::Nonterm & nonterm);
    basl::Token & getAccess () const;
    basl::Token & getVirtualOpt () const;
    basl::Nonterm & getObjName () const;
    basl::Nonterm & getBaseInit () const;
  };
}
namespace gram
{
  class DirectDcl5Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    DirectDcl5Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjDclId () const;
    basl::Nonterm & getParamDecl1Body () const;
    basl::Nonterm & getParamDecl2Body () const;
    basl::Token & getRPAREN_TOKEN () const;
    basl::Nonterm & getCvSpecSeqOpt () const;
    basl::Nonterm & getThrowSpecOpt () const;
  };
}
namespace gram
{
  class FunctorDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    FunctorDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getFunctorDecl () const;
    basl::Nonterm & getLazyBaseClauseOpt () const;
    basl::Token & getTryOpt () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
    basl::Nonterm & getHandlerSeqOpt () const;
  };
}
namespace gram
{
  class FunctorDeclTypeNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    FunctorDeclTypeNode (basl::Nonterm & nonterm);
    basl::Nonterm & getFunctorDecl () const;
    basl::Nonterm & getLazyBaseClauseOpt () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class EnumDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    EnumDefNode (basl::Nonterm & nonterm);
    basl::Token & getENUM_TOKEN () const;
    basl::Nonterm & getObjNameOpt () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Nonterm & getEnumBodyOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
    basl::Token & getSemiOpt () const;
  };
}
namespace gram
{
  class EnumtorDecl1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    EnumtorDecl1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
  };
}
namespace gram
{
  class EnumtorDecl2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    EnumtorDecl2Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
    basl::Token & getASSIGN_TOKEN () const;
    basl::Token & getBLOCK_TOKEN () const;
  };
}
namespace gram
{
  class UsingDeclNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    UsingDeclNode (basl::Nonterm & nonterm);
    basl::Token & getUSING_TOKEN () const;
    basl::Nonterm & getObjName () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class UsingDirNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    UsingDirNode (basl::Nonterm & nonterm);
    basl::Token & getUSING_TOKEN () const;
    basl::Token & getNAMESPACE_TOKEN () const;
    basl::Nonterm & getObjName () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class LinkageSpecNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LinkageSpecNode (basl::Nonterm & nonterm);
    basl::Nonterm & getLinkageBlockBegin () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Nonterm & getDeclSeqOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
  };
}
namespace gram
{
  class LinkageBlockBeginNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LinkageBlockBeginNode (basl::Nonterm & nonterm);
    basl::Token & getEXTERN_TOKEN () const;
    basl::Token & getLITERAL_STRING_TOKEN () const;
  };
}
namespace gram
{
  class LinkageDeclBeginNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    LinkageDeclBeginNode (basl::Nonterm & nonterm);
    basl::Token & getEXTERN_TOKEN () const;
    basl::Token & getLITERAL_STRING_TOKEN () const;
  };
}
namespace gram
{
  class NavDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NavDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getNavHead () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Nonterm & getNavSpecSeqOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
  };
}
namespace gram
{
  class NavHeadNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NavHeadNode (basl::Nonterm & nonterm);
    basl::Token & getNAVIGATOR_TOKEN () const;
    basl::Nonterm & getNavDecl () const;
    basl::Nonterm & getLazyBaseClauseOpt () const;
  };
}
namespace gram
{
  class NavDirectDcl1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NavDirectDcl1Node (basl::Nonterm & nonterm);
    basl::Nonterm & getObjDclId () const;
    basl::Token & getLPAREN_TOKEN () const;
    basl::Nonterm & getNavNodeType () const;
    basl::Token & getRPAREN_TOKEN1 () const;
    basl::Nonterm & getParamDecl1Body () const;
    basl::Token & getRPAREN_TOKEN2 () const;
  };
}
namespace gram
{
  class NavVisitFuncDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    NavVisitFuncDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName1 () const;
    basl::Token & getLPAREN_TOKEN () const;
    basl::Nonterm & getObjName2 () const;
    basl::Token & getRPAREN_TOKEN () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
  };
}
namespace gram
{
  class ReturnStmtNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ReturnStmtNode (basl::Nonterm & nonterm);
    basl::Token & getRETURN_TOKEN () const;
    basl::Token & getBLOCK_TOKEN () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class VdfDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getVdfHead () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Nonterm & getVdfSpecSeqOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
  };
}
namespace gram
{
  class VdfHeadNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfHeadNode (basl::Nonterm & nonterm);
    basl::Token & getVDF_TOKEN () const;
    basl::Nonterm & getFuncDecl () const;
  };
}
namespace gram
{
  class VdfFunctorDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfFunctorDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getObjName () const;
    basl::Nonterm & getParamDecl1Body () const;
    basl::Token & getRPAREN_TOKEN () const;
    basl::Token & getTryOpt () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
    basl::Nonterm & getHandlerSeqOpt () const;
  };
}
namespace gram
{
  class VdfShortData1DefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfShortData1DefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getXUxxDeclSpecSeq () const;
    basl::Token & getIDENT_TOKEN () const;
    basl::Nonterm & getVdfDataParamListAltOpt () const;
    basl::Nonterm & getVdfDirectObjInitOpt () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class VdfShortData2DefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfShortData2DefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getXUxxDeclSpecSeq () const;
    basl::Token & getLITERAL_STRING_TOKEN () const;
    basl::Nonterm & getVdfDataParamListAltOpt () const;
    basl::Nonterm & getVdfDirectObjInitOpt () const;
    basl::Token & getSEMI_TOKEN () const;
  };
}
namespace gram
{
  class VdfDataParamListNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfDataParamListNode (basl::Nonterm & nonterm);
    basl::Token & getLPAREN_TOKEN () const;
    basl::Token & getBlockOpt () const;
    basl::Token & getRPAREN_TOKEN () const;
  };
}
namespace gram
{
  class ObjInit4Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    ObjInit4Node (basl::Nonterm & nonterm);
    basl::Token & getLPAREN_TOKEN () const;
    basl::Token & getBLOCK_TOKEN () const;
    basl::Token & getRPAREN_TOKEN () const;
  };
}
namespace gram
{
  class VdfBlockDataDefNode : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfBlockDataDefNode (basl::Nonterm & nonterm);
    basl::Nonterm & getVdfBlockDataHead () const;
    basl::Token & getLBRACE_TOKEN () const;
    basl::Nonterm & getSimpleVdfObjDeclSeqOpt () const;
    basl::Nonterm & getReturnStmtOpt () const;
    basl::Token & getRBRACE_TOKEN () const;
  };
}
namespace gram
{
  class VdfBlockDataHead1Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfBlockDataHead1Node (basl::Nonterm & nonterm);
    basl::Token & getIDENT_TOKEN () const;
    basl::Nonterm & getVdfDataParamListAltOpt () const;
  };
}
namespace gram
{
  class VdfBlockDataHead2Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    VdfBlockDataHead2Node (basl::Nonterm & nonterm);
    basl::Token & getLITERAL_STRING_TOKEN () const;
    basl::Nonterm & getVdfDataParamListAltOpt () const;
  };
}
namespace gram
{
  class DirectDcl6Node : public basl::NontermProxy
  {
  public:
    static basl::NontermInfo const info;
    DirectDcl6Node (basl::Nonterm & nonterm);
    basl::Nonterm & getVdfObjBDirectDcl () const;
    basl::Nonterm & getVdfDataParamList () const;
    basl::Nonterm & getCvSpecSeqOpt () const;
    basl::Nonterm & getThrowSpecOpt () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_Nonterm.inl"
#endif
#endif
