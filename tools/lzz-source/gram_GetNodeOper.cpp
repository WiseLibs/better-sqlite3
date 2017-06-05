// gram_GetNodeOper.cpp
//

#include "gram_GetNodeOper.h"
// gram
#include "gram_GetOperKind.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetNodeOper : Visitor
  {
    smtc::OperKind & kind;
    void visit (Oper1Node & node) const;
    void visit (Oper2Node & node) const;
    void visit (Oper3Node & node) const;
    void visit (Oper4Node & node) const;
    void visit (Oper5Node & node) const;
  public:
    explicit GetNodeOper (smtc::OperKind & kind);
    ~ GetNodeOper ();
  };
}
namespace
{
  void GetNodeOper::visit (Oper1Node & node) const
    {
      kind = smtc::CALL_OPER;
    }
}
namespace
{
  void GetNodeOper::visit (Oper2Node & node) const
    {
      kind = smtc::SUBSCR_OPER;
    }
}
namespace
{
  void GetNodeOper::visit (Oper3Node & node) const
    {
      kind = smtc::NEW_ARRAY_OPER;
    }
}
namespace
{
  void GetNodeOper::visit (Oper4Node & node) const
    {
      kind = smtc::DELETE_OPER;
    }
}
namespace
{
  void GetNodeOper::visit (Oper5Node & node) const
    {
      kind = getOperKind (node.getSingleOper ().getNumber ());
    }
}
namespace
{
  LZZ_INLINE GetNodeOper::GetNodeOper (smtc::OperKind & kind)
    : kind (kind)
         {}
}
namespace
{
  GetNodeOper::~ GetNodeOper ()
         {}
}
namespace gram
{
  smtc::OperKind getNodeOper (basl::Nonterm & nonterm)
  {
    smtc::OperKind kind;
    nonterm.accept (GetNodeOper (kind));
    return kind;
  }
}
#undef LZZ_INLINE
