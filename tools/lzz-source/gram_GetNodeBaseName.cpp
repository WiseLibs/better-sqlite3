// gram_GetNodeBaseName.cpp
//

#include "gram_GetNodeBaseName.h"
// std lib
#include <cassert>

// gram
#include "gram_GetNodeDcl.h"
#include "gram_GetNodeOper.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_CreateConvBaseName.h"
#include "smtc_CreateDtorBaseName.h"
#include "smtc_CreateIdentBaseName.h"
#include "smtc_CreateOperBaseName.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeBaseName : Visitor
  {
    smtc::BaseNamePtr & base_name;
    void visit (BaseName1Node & node) const;
    void visit (BaseName2Node & node) const;
    void visit (BaseName3Node & node) const;
    void visit (BaseName4Node & node) const;
  public:
    explicit GetNodeBaseName (smtc::BaseNamePtr & base_name);
    ~ GetNodeBaseName ();
  };
}
namespace
{
  void GetNodeBaseName::visit (BaseName1Node & node) const
    {
      util::Ident macro;
      if (node.getMacroOpt ().isSet ())
      {
        macro = node.getMacroOpt ().getLexeme ();
      }
      base_name = smtc::createIdentBaseName (node.getIDENT_TOKEN ().getLoc (), macro, node.getIDENT_TOKEN ().getLexeme ());
    }
}
namespace
{
  void GetNodeBaseName::visit (BaseName2Node & node) const
    {
      util::Ident macro;
      if (node.getMacroOpt ().isSet ())
      {
        macro = node.getMacroOpt ().getLexeme ();
      }
      base_name = smtc::createDtorBaseName (node.getBITNOT_TOKEN ().getLoc (), macro, node.getIDENT_TOKEN ().getLexeme ());
    }
}
namespace
{
  void GetNodeBaseName::visit (BaseName3Node & node) const
    {
      util::Ident macro;
      if (node.getMacroOpt ().isSet ())
      {
        macro = node.getMacroOpt ().getLexeme ();
      }
      smtc::OperKind kind = getNodeOper (node.getOper ());
      base_name = smtc::createOperBaseName (node.getOPERATOR_TOKEN ().getLoc (), macro, kind);
    }
}
namespace
{
  void GetNodeBaseName::visit (BaseName4Node & node) const
    {
      util::Ident macro;
      if (node.getMacroOpt ().isSet ())
      {
        macro = node.getMacroOpt ().getLexeme ();
      }
      smtc::CvType cv_type;
      getNodeAbstractDcl (node.getAbstractDecl (), cv_type);
      base_name = smtc::createConvBaseName (node.getOPERATOR_TOKEN ().getLoc (), macro, cv_type);
    }
}
namespace
{
  LZZ_INLINE GetNodeBaseName::GetNodeBaseName (smtc::BaseNamePtr & base_name)
    : Visitor (), base_name (base_name)
         {}
}
namespace
{
  GetNodeBaseName::~ GetNodeBaseName ()
         {}
}
namespace gram
{
  smtc::BaseNamePtr getNodeBaseName (basl::Nonterm & nonterm)
  {
    smtc::BaseNamePtr base_name;
    nonterm.accept (GetNodeBaseName (base_name));
    assert (base_name.isSet ());
    return base_name;
  }
}
#undef LZZ_INLINE
