// gram_Nonterm.inl
//

#include "basl_Node.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE SimpleDeclNode::SimpleDeclNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & SimpleDeclNode::getNestedSimpleDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & SimpleDeclNode::getSEMI_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE NestedSimpleDecl1Node::NestedSimpleDecl1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NestedSimpleDecl1Node::getNestedObjDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NestedSimpleDecl1Node::getObjInitOpt () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE NestedSimpleDecl2Node::NestedSimpleDecl2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NestedSimpleDecl2Node::getNestedFuncDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE NestedSimpleDecl3Node::NestedSimpleDecl3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NestedSimpleDecl3Node::getNestedBitfDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE NestedDeclNode::NestedDeclNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NestedDeclNode::getNestedSimpleDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NestedDeclNode::getCOMMA_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NestedDeclNode::getObjDcl () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE ObjInit1Node::ObjInit1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit1Node::getASSIGN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit1Node::getBLOCK_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ObjInit2Node::ObjInit2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit2Node::getDINIT_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit2Node::getLPAREN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ObjInit2Node::getExprList () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit2Node::getRPAREN_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ObjInit3Node::ObjInit3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ObjInit3Node::getDirectExprList () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit3Node::getRPAREN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE BlockNode::BlockNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & BlockNode::getBLOCK_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE NestedName1Node::NestedName1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & NestedName1Node::getDCOLON_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE NestedName2Node::NestedName2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NestedName2Node::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NestedName2Node::getDCOLON_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Name1Node::Name1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Name1Node::getNestedNameOpt () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Name1Node::getObjBaseName () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE Name2Node::Name2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Name2Node::getNestedNameOpt () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Name2Node::getObjBaseName () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name2Node::getLT_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name2Node::getBlockOpt () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name2Node::getGT_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Name3Node::Name3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Name3Node::getNestedName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name3Node::getTEMPLATE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Name3Node::getObjBaseName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name3Node::getLT_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name3Node::getBlockOpt () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name3Node::getGT_TOKEN () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE BaseName1Node::BaseName1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName1Node::getMacroOpt () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName1Node::getIDENT_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Name4Node::Name4Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Name4Node::getNestedNameOpt () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name4Node::getMacroOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name4Node::getIDENT_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name4Node::getCOLON_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name4Node::getBLOCK_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Name5Node::Name5Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & Name5Node::getCOLON_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Name5Node::getBLOCK_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE BaseName2Node::BaseName2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName2Node::getMacroOpt () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName2Node::getBITNOT_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName2Node::getIDENT_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE BaseName3Node::BaseName3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName3Node::getMacroOpt () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName3Node::getOPERATOR_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & BaseName3Node::getOper () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE BaseName4Node::BaseName4Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName4Node::getMacroOpt () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseName4Node::getOPERATOR_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & BaseName4Node::getAbstractDecl () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE Oper1Node::Oper1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper1Node::getLPAREN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper1Node::getRPAREN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Oper2Node::Oper2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper2Node::getLBRACK_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper2Node::getRBRACK_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Oper3Node::Oper3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper3Node::getNEW_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper3Node::getLBRACK_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper3Node::getRBRACK_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Oper4Node::Oper4Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper4Node::getDELETE_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper4Node::getLBRACK_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper4Node::getRBRACK_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Oper5Node::Oper5Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & Oper5Node::getSingleOper () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE DeclSpecNode::DeclSpecNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & DeclSpecNode::getTYPEDEF_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE CVSpecNode::CVSpecNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & CVSpecNode::getCvToken () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE SeqNode::SeqNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & SeqNode::getCvSpecSeq () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & SeqNode::getCvSpec () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE FtorSpecNode::FtorSpecNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & FtorSpecNode::getFtorToken () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE UserTypeNode::UserTypeNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & UserTypeNode::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE ElabTypeNode::ElabTypeNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & ElabTypeNode::getClassKey () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ElabTypeNode::getDllApiOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ElabTypeNode::getObjName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE BuiltInTypeNode::BuiltInTypeNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & BuiltInTypeNode::getBuiltInTypeToken () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE DclNode::DclNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DclNode::getPtrOper () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DclNode::getObjADcl () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE DirectDcl1Node::DirectDcl1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl1Node::getObjBDirectDcl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl1Node::getParamDecl1Body () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & DirectDcl1Node::getRPAREN_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl1Node::getCvSpecSeqOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl1Node::getThrowSpecOpt () const
    {
      return getChild (5).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE DirectDcl2Node::DirectDcl2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl2Node::getObjADirectDcl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & DirectDcl2Node::getLBRACK_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & DirectDcl2Node::getBlockOpt () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & DirectDcl2Node::getRBRACK_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE DirectDcl3Node::DirectDcl3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & DirectDcl3Node::getLPAREN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl3Node::getObjBDcl () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & DirectDcl3Node::getRPAREN_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE PureDclNode::PureDclNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & PureDclNode::getFuncDcl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & PureDclNode::getPureOpt () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE PureNode::PureNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & PureNode::getASSIGN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & PureNode::getZERO_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE DirectDcl4Node::DirectDcl4Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl4Node::getObjDclId () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl4Node::getParamDecl1Body () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & DirectDcl4Node::getRPAREN_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl4Node::getCvSpecSeqOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl4Node::getThrowSpecOpt () const
    {
      return getChild (5).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE PtrOper1Node::PtrOper1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & PtrOper1Node::getTIMES_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & PtrOper1Node::getCvSpecSeqOpt () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE PtrOper2Node::PtrOper2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & PtrOper2Node::getBITAND_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE PtrOper3Node::PtrOper3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & PtrOper3Node::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & PtrOper3Node::getDCOLON_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & PtrOper3Node::getTIMES_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & PtrOper3Node::getCvSpecSeqOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE IdNode::IdNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & IdNode::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE ParamDeclBody1Node::ParamDeclBody1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ParamDeclBody1Node::getParamDecl1List () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDeclBody1Node::getEllipseOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ParamDeclBody2Node::ParamDeclBody2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ParamDeclBody2Node::getParamDecl1List () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDeclBody2Node::getCOMMA_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDeclBody2Node::getELLIPSE_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ParamDeclBody3Node::ParamDeclBody3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDeclBody3Node::getLPAREN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDeclBody3Node::getEllipseOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ParamDeclBody4Node::ParamDeclBody4Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDeclBody4Node::getLPAREN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDeclBody4Node::getVOID_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ParamDecl1Node::ParamDecl1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ParamDecl1Node::getParamDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE ParamDecl2Node::ParamDecl2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ParamDecl2Node::getParamDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDecl2Node::getASSIGN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ParamDecl2Node::getBLOCK_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE Decl2Node::Decl2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Decl2Node::getXBxxDeclSpecSeq () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Decl2Node::getObjDcl () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE Decl1Node::Decl1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & Decl1Node::getPureCtorDcl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE TypeIdNode::TypeIdNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TypeIdNode::getAbstractDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE NamespaceDefNode::NamespaceDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NamespaceDefNode::getNamespaceHead () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NamespaceDefNode::getLBRACE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NamespaceDefNode::getDeclSeqOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NamespaceDefNode::getRBRACE_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE NamespaceHead1Node::NamespaceHead1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & NamespaceHead1Node::getNAMESPACE_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NamespaceHead1Node::getObjName () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE NamespaceHead2Node::NamespaceHead2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & NamespaceHead2Node::getNAMESPACE_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ClassDefNode::ClassDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ClassDefNode::getClassHead () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ClassDefNode::getLBRACE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ClassDefNode::getMbrDeclSeqOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ClassDefNode::getRBRACE_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ClassDefNode::getSemiOpt () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ClassHeadNode::ClassHeadNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & ClassHeadNode::getClassKey () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ClassHeadNode::getDllApiOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ClassHeadNode::getObjName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ClassHeadNode::getBaseClauseOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE BaseSpec1Node::BaseSpec1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & BaseSpec1Node::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE BaseSpec2Node::BaseSpec2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseSpec2Node::getVIRTUAL_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseSpec2Node::getAccessOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & BaseSpec2Node::getObjName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE BaseSpec3Node::BaseSpec3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseSpec3Node::getAccess () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & BaseSpec3Node::getVirtualOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & BaseSpec3Node::getObjName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE AccessSpecNode::AccessSpecNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & AccessSpecNode::getAccess () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & AccessSpecNode::getCOLON_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ClassDeclNode::ClassDeclNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & ClassDeclNode::getXExxDeclSpecSeq () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ClassDeclNode::getSEMI_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE FriendClassDeclNode::FriendClassDeclNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FriendClassDeclNode::getFExxDeclSpecSeq () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FriendClassDeclNode::getSEMI_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE FuncDefNode::FuncDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FuncDefNode::getFuncDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FuncDefNode::getTryOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FuncDefNode::getCtorInitOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FuncDefNode::getLBRACE_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FuncDefNode::getBlockOpt () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FuncDefNode::getRBRACE_TOKEN () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FuncDefNode::getHandlerSeqOpt () const
    {
      return getChild (7).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE MbrInitNode::MbrInitNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & MbrInitNode::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & MbrInitNode::getLPAREN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & MbrInitNode::getExprListOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & MbrInitNode::getRPAREN_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE HandlerNode::HandlerNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & HandlerNode::getCATCH_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & HandlerNode::getLPAREN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & HandlerNode::getCatchDecl () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & HandlerNode::getRPAREN_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & HandlerNode::getLBRACE_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & HandlerNode::getBlockOpt () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & HandlerNode::getRBRACE_TOKEN () const
    {
      return getChild (7).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE TmplDeclNode::TmplDeclNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplDeclNode::getTmplSpec () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplDeclNode::getTmplSpecDecl () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE TmplSpecNode::TmplSpecNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplSpecNode::getTEMPLATE_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplSpecNode::getLT_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplSpecNode::getTmplParamListOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplSpecNode::getGT_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE TypeParam1Node::TypeParam1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & TypeParam1Node::getTypeKey () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TypeParam1Node::getObjName () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE TypeParam2Node::TypeParam2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & TypeParam2Node::getTypeKey () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TypeParam2Node::getObjName () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TypeParam2Node::getASSIGN_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TypeParam2Node::getAbstractDecl () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE TmplTmplParam1Node::TmplTmplParam1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam1Node::getTEMPLATE_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam1Node::getLT_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplTmplParam1Node::getTmplParamListOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam1Node::getGT_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam1Node::getCLASS_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplTmplParam1Node::getObjName () const
    {
      return getChild (6).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE TmplTmplParam2Node::TmplTmplParam2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam2Node::getTEMPLATE_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam2Node::getLT_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplTmplParam2Node::getTmplParamListOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam2Node::getGT_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam2Node::getCLASS_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplTmplParam2Node::getObjName1 () const
    {
      return getChild (6).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplTmplParam2Node::getASSIGN_TOKEN () const
    {
      return getChild (7).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplTmplParam2Node::getObjName2 () const
    {
      return getChild (8).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE TmplInstNode::TmplInstNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplInstNode::getTmplInstBegin () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & TmplInstNode::getTmplInstDecl () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE TmplInstBeginNode::TmplInstBeginNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & TmplInstBeginNode::getTEMPLATE_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE LazyCtorNode::LazyCtorNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorNode::getLazyCtorBegin () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorNode::getLBRACE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorNode::getMbrDeclSeqOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorNode::getRBRACE_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorNode::getSemiOpt () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE LazyCtorBegin1Node::LazyCtorBegin1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorBegin1Node::getClassKey () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorBegin1Node::getDllApiOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorBegin1Node::getObjName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorBegin1Node::getParamDecl1Body () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorBegin1Node::getRPAREN_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorBegin1Node::getLazyBaseClauseOpt () const
    {
      return getChild (6).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE LazyCtorBegin2Node::LazyCtorBegin2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorBegin2Node::getXxxSDeclSpecSeq () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorBegin2Node::getClassKey () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorBegin2Node::getDllApiOpt () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorBegin2Node::getObjName () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorBegin2Node::getParamDecl1Body () const
    {
      return getChild (5).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyCtorBegin2Node::getRPAREN_TOKEN () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyCtorBegin2Node::getLazyBaseClauseOpt () const
    {
      return getChild (7).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE LazyBaseSpec1Node::LazyBaseSpec1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyBaseSpec1Node::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyBaseSpec1Node::getBaseInit () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE LazyBaseSpec2Node::LazyBaseSpec2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyBaseSpec2Node::getVIRTUAL_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyBaseSpec2Node::getAccessOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyBaseSpec2Node::getObjName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyBaseSpec2Node::getBaseInit () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE LazyBaseSpec3Node::LazyBaseSpec3Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyBaseSpec3Node::getAccess () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LazyBaseSpec3Node::getVirtualOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyBaseSpec3Node::getObjName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LazyBaseSpec3Node::getBaseInit () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE DirectDcl5Node::DirectDcl5Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl5Node::getObjDclId () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl5Node::getParamDecl1Body () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl5Node::getParamDecl2Body () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & DirectDcl5Node::getRPAREN_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl5Node::getCvSpecSeqOpt () const
    {
      return getChild (5).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl5Node::getThrowSpecOpt () const
    {
      return getChild (6).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE FunctorDefNode::FunctorDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FunctorDefNode::getFunctorDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FunctorDefNode::getLazyBaseClauseOpt () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FunctorDefNode::getTryOpt () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FunctorDefNode::getLBRACE_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FunctorDefNode::getBlockOpt () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FunctorDefNode::getRBRACE_TOKEN () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FunctorDefNode::getHandlerSeqOpt () const
    {
      return getChild (7).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE FunctorDeclTypeNode::FunctorDeclTypeNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FunctorDeclTypeNode::getFunctorDecl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & FunctorDeclTypeNode::getLazyBaseClauseOpt () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & FunctorDeclTypeNode::getSEMI_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE EnumDefNode::EnumDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & EnumDefNode::getENUM_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & EnumDefNode::getObjNameOpt () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & EnumDefNode::getLBRACE_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & EnumDefNode::getEnumBodyOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & EnumDefNode::getRBRACE_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & EnumDefNode::getSemiOpt () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE EnumtorDecl1Node::EnumtorDecl1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & EnumtorDecl1Node::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE EnumtorDecl2Node::EnumtorDecl2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & EnumtorDecl2Node::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & EnumtorDecl2Node::getASSIGN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & EnumtorDecl2Node::getBLOCK_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE UsingDeclNode::UsingDeclNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & UsingDeclNode::getUSING_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & UsingDeclNode::getObjName () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & UsingDeclNode::getSEMI_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE UsingDirNode::UsingDirNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & UsingDirNode::getUSING_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & UsingDirNode::getNAMESPACE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & UsingDirNode::getObjName () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & UsingDirNode::getSEMI_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE LinkageSpecNode::LinkageSpecNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LinkageSpecNode::getLinkageBlockBegin () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LinkageSpecNode::getLBRACE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & LinkageSpecNode::getDeclSeqOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LinkageSpecNode::getRBRACE_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE LinkageBlockBeginNode::LinkageBlockBeginNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & LinkageBlockBeginNode::getEXTERN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LinkageBlockBeginNode::getLITERAL_STRING_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE LinkageDeclBeginNode::LinkageDeclBeginNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & LinkageDeclBeginNode::getEXTERN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & LinkageDeclBeginNode::getLITERAL_STRING_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE NavDefNode::NavDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavDefNode::getNavHead () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavDefNode::getLBRACE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavDefNode::getNavSpecSeqOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavDefNode::getRBRACE_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE NavHeadNode::NavHeadNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & NavHeadNode::getNAVIGATOR_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavHeadNode::getNavDecl () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavHeadNode::getLazyBaseClauseOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE NavDirectDcl1Node::NavDirectDcl1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavDirectDcl1Node::getObjDclId () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavDirectDcl1Node::getLPAREN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavDirectDcl1Node::getNavNodeType () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavDirectDcl1Node::getRPAREN_TOKEN1 () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavDirectDcl1Node::getParamDecl1Body () const
    {
      return getChild (5).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavDirectDcl1Node::getRPAREN_TOKEN2 () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE NavVisitFuncDefNode::NavVisitFuncDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavVisitFuncDefNode::getObjName1 () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavVisitFuncDefNode::getLPAREN_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & NavVisitFuncDefNode::getObjName2 () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavVisitFuncDefNode::getRPAREN_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavVisitFuncDefNode::getLBRACE_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavVisitFuncDefNode::getBlockOpt () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & NavVisitFuncDefNode::getRBRACE_TOKEN () const
    {
      return getChild (7).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ReturnStmtNode::ReturnStmtNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & ReturnStmtNode::getRETURN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ReturnStmtNode::getBLOCK_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ReturnStmtNode::getSEMI_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE VdfDefNode::VdfDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfDefNode::getVdfHead () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfDefNode::getLBRACE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfDefNode::getVdfSpecSeqOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfDefNode::getRBRACE_TOKEN () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE VdfHeadNode::VdfHeadNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfHeadNode::getVDF_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfHeadNode::getFuncDecl () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE VdfFunctorDefNode::VdfFunctorDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfFunctorDefNode::getObjName () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfFunctorDefNode::getParamDecl1Body () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfFunctorDefNode::getRPAREN_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfFunctorDefNode::getTryOpt () const
    {
      return getChild (4).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfFunctorDefNode::getLBRACE_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfFunctorDefNode::getBlockOpt () const
    {
      return getChild (6).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfFunctorDefNode::getRBRACE_TOKEN () const
    {
      return getChild (7).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfFunctorDefNode::getHandlerSeqOpt () const
    {
      return getChild (8).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE VdfShortData1DefNode::VdfShortData1DefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfShortData1DefNode::getXUxxDeclSpecSeq () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfShortData1DefNode::getIDENT_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfShortData1DefNode::getVdfDataParamListAltOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfShortData1DefNode::getVdfDirectObjInitOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfShortData1DefNode::getSEMI_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE VdfShortData2DefNode::VdfShortData2DefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfShortData2DefNode::getXUxxDeclSpecSeq () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfShortData2DefNode::getLITERAL_STRING_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfShortData2DefNode::getVdfDataParamListAltOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfShortData2DefNode::getVdfDirectObjInitOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfShortData2DefNode::getSEMI_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE VdfDataParamListNode::VdfDataParamListNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfDataParamListNode::getLPAREN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfDataParamListNode::getBlockOpt () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfDataParamListNode::getRPAREN_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE ObjInit4Node::ObjInit4Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit4Node::getLPAREN_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit4Node::getBLOCK_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & ObjInit4Node::getRPAREN_TOKEN () const
    {
      return getChild (3).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE VdfBlockDataDefNode::VdfBlockDataDefNode (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfBlockDataDefNode::getVdfBlockDataHead () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfBlockDataDefNode::getLBRACE_TOKEN () const
    {
      return getChild (2).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfBlockDataDefNode::getSimpleVdfObjDeclSeqOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfBlockDataDefNode::getReturnStmtOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfBlockDataDefNode::getRBRACE_TOKEN () const
    {
      return getChild (5).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE VdfBlockDataHead1Node::VdfBlockDataHead1Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfBlockDataHead1Node::getIDENT_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfBlockDataHead1Node::getVdfDataParamListAltOpt () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE VdfBlockDataHead2Node::VdfBlockDataHead2Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Token & VdfBlockDataHead2Node::getLITERAL_STRING_TOKEN () const
    {
      return getChild (1).getToken ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & VdfBlockDataHead2Node::getVdfDataParamListAltOpt () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE DirectDcl6Node::DirectDcl6Node (basl::Nonterm & nonterm)
    : basl::NontermProxy (nonterm)
    {}
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl6Node::getVdfObjBDirectDcl () const
    {
      return getChild (1).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl6Node::getVdfDataParamList () const
    {
      return getChild (2).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl6Node::getCvSpecSeqOpt () const
    {
      return getChild (3).getNonterm ();
    }
}
namespace gram
{
  LZZ_INLINE basl::Nonterm & DirectDcl6Node::getThrowSpecOpt () const
    {
      return getChild (4).getNonterm ();
    }
}
#undef LZZ_INLINE
