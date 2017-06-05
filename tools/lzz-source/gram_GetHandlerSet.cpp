// gram_GetHandlerSet.cpp
//

#include "gram_GetHandlerSet.h"
// gram
#include "gram_BlockTable.h"
#include "gram_CharBlock.h"
#include "gram_GetNodeDcl.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_CreateHandler.h"
#include "smtc_GetCatchParam.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetHandlerSet : Visitor
  {
    smtc::HandlerPtrVector & handler_set;
    void visit (HandlerNode & node) const;
  public:
    explicit GetHandlerSet (smtc::HandlerPtrVector & handler_set);
    ~ GetHandlerSet ();
  };
}
namespace
{
  void GetHandlerSet::visit (HandlerNode & node) const
    {
      SpecSel dcl_spec_sel;
      smtc::CvType cv_type;
      smtc::NamePtr name;
      getNodeParamDcl (node.getCatchDecl (), dcl_spec_sel, cv_type, name);
      smtc::ParamPtr catch_decl;
      if (name.isSet ())
      {
        catch_decl = smtc::getCatchParam (dcl_spec_sel, cv_type, name);
      }
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
      handler_set.push_back (smtc::createHandler (node.getCATCH_TOKEN ().getLoc (), catch_decl, body));
    }
}
namespace
{
  LZZ_INLINE GetHandlerSet::GetHandlerSet (smtc::HandlerPtrVector & handler_set)
    : handler_set (handler_set)
         {}
}
namespace
{
  GetHandlerSet::~ GetHandlerSet ()
         {}
}
namespace gram
{
  void getHandlerSet (basl::Nonterm & nonterm, smtc::HandlerPtrVector & handler_set)
  {
    nonterm.accept (GetHandlerSet (handler_set));
  }
}
#undef LZZ_INLINE
