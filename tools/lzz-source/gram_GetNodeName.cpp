// gram_GetNodeName.cpp
//

#include "gram_GetNodeName.h"
// gram
#include "gram_BlockTable.h"
#include "gram_GetNodeBaseName.h"
#include "gram_Message.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_CreateBitfName.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateQualName.h"
#include "smtc_CreateTmplName.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeName : Visitor
  {
    smtc::NamePtr & name;
    static smtc::NamePtr visitNode (basl::Nonterm & nonterm);
    void visit (NestedName1Node & node) const;
    void visit (NestedName2Node & node) const;
    void visit (Name1Node & node) const;
    void visit (Name2Node & node) const;
    void visit (Name3Node & node) const;
    void visit (Name4Node & node) const;
    void visit (Name5Node & node) const;
  public:
    explicit GetNodeName (smtc::NamePtr & name);
    ~ GetNodeName ();
  };
}
namespace
{
  smtc::NamePtr GetNodeName::visitNode (basl::Nonterm & nonterm)
    {
      smtc::NamePtr name;
      nonterm.accept (GetNodeName (name));
      return name;
    }
}
namespace
{
  void GetNodeName::visit (NestedName1Node & node) const
    {}
}
namespace
{
  void GetNodeName::visit (NestedName2Node & node) const
    {
      name = visitNode (node.getObjName ());
    }
}
namespace
{
  void GetNodeName::visit (Name1Node & node) const
    {
      name = smtc::createNonTmplName (getNodeBaseName (node.getObjBaseName ()));
      basl::Nonterm & nested_name = node.getNestedNameOpt ();
      if (nested_name.isSet ())
      {
        name = smtc::createQualName (visitNode (nested_name), name);
      }
    }
}
namespace
{
  void GetNodeName::visit (Name2Node & node) const
    {
      util::String args;
      basl::Token block_token = node.getBlockOpt ();
      if (block_token.isSet ())
      {
        args = getBlock (block_token.getLexeme ()).toString ();
      }
      name = smtc::createTmplName (getNodeBaseName (node.getObjBaseName ()), false, args);
      basl::Nonterm & nested_name = node.getNestedNameOpt ();
      if (nested_name.isSet ())
      {
        name = smtc::createQualName (visitNode (nested_name), name);
      }
    }
}
namespace
{
  void GetNodeName::visit (Name3Node & node) const
    {
      util::String args;
      basl::Token block_token = node.getBlockOpt ();
      if (block_token.isSet ())
      {
        args = getBlock (block_token.getLexeme ()).toString ();
      }
      name = smtc::createTmplName (getNodeBaseName (node.getObjBaseName ()), true, args);
      basl::Nonterm & nested_name = node.getNestedName ();
      name = smtc::createQualName (visitNode (nested_name), name);
    }
}
namespace
{
  void GetNodeName::visit (Name4Node & node) const
    {
      // cannot be qualified
      util::Loc const & loc = node.getIDENT_TOKEN ().getLoc ();
      if (node.getNestedNameOpt ().isSet ())
      {
        msg::qualBitfield (loc);
      }
      Block block = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      name = smtc::createBitfName (loc, node.getIDENT_TOKEN ().getLexeme (), block);
    }
}
namespace
{
  void GetNodeName::visit (Name5Node & node) const
    {
      // cannot be qualified
      util::Loc const & loc = node.getCOLON_TOKEN ().getLoc ();
      Block block = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      name = smtc::createBitfName (loc, util::Ident (), block);
    }
}
namespace
{
  LZZ_INLINE GetNodeName::GetNodeName (smtc::NamePtr & name)
    : Visitor (), name (name)
         {}
}
namespace
{
  GetNodeName::~ GetNodeName ()
         {}
}
namespace gram
{
  smtc::NamePtr getNodeName (basl::Nonterm & nonterm)
  {
    return GetNodeName::visitNode (nonterm);
  }
}
#undef LZZ_INLINE
