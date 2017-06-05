// gram_GetNodeCvSpecSeq.cpp
//

#include "gram_GetNodeCvSpecSeq.h"
// gram
#include "gram_Message.h"
#include "gram_Nonterm.h"
#include "gram_TokenNumber.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_GetCv.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeCvSpecSeq : Visitor
  {
    bool & c;
    bool & v;
    void visit (CVSpecNode & node) const;
  public:
    explicit GetNodeCvSpecSeq (bool & c, bool & v);
    ~ GetNodeCvSpecSeq ();
  };
}
namespace
{
  void GetNodeCvSpecSeq::visit (CVSpecNode & node) const
    {
      util::Loc const & loc = node.getCvToken ().getLoc ();
      if (node.getCvToken ().getNumber () == CONST_TOKEN)
      {
        if (c)
        {
          msg::duplicateSpecifier (loc, "const");
        }
        else
        {
          c = true;
        }
      }
      else if (v)
      {
        msg::duplicateSpecifier (loc, "volatile");
      }
      else
      {
        v = true;
      }
    }
}
namespace
{
  LZZ_INLINE GetNodeCvSpecSeq::GetNodeCvSpecSeq (bool & c, bool & v)
    : c (c), v (v)
         {}
}
namespace
{
  GetNodeCvSpecSeq::~ GetNodeCvSpecSeq ()
         {}
}
namespace gram
{
  smtc::Cv getNodeCvSpecSeq (basl::Nonterm & nonterm)
  {
    bool c = false, v = false;
    nonterm.accept (GetNodeCvSpecSeq (c, v));
    return smtc::getCv (c, v);
  }
}
#undef LZZ_INLINE
