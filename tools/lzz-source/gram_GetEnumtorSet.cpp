// gram_GetEnumtorSet.cpp
//

#include "gram_GetEnumtorSet.h"
// gram
#include "gram_BlockTable.h"
#include "gram_GetNodeName.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_GetEnumtor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetEnumtorSet : Visitor
  {
    smtc::EnumtorPtrVector & enumtor_set;
    void visit (EnumtorDecl1Node & node) const;
    void visit (EnumtorDecl2Node & node) const;
  public:
    explicit GetEnumtorSet (smtc::EnumtorPtrVector & enumtor_set);
    ~ GetEnumtorSet ();
  };
}
namespace
{
  void GetEnumtorSet::visit (EnumtorDecl1Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      enumtor_set.push_back (smtc::getEnumtor (name));
    }
}
namespace
{
  void GetEnumtorSet::visit (EnumtorDecl2Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      Block init = getBlock (node.getBLOCK_TOKEN ().getLexeme ());
      enumtor_set.push_back (smtc::getEnumtor (name, init));
    }
}
namespace
{
  LZZ_INLINE GetEnumtorSet::GetEnumtorSet (smtc::EnumtorPtrVector & enumtor_set)
    : enumtor_set (enumtor_set)
         {}
}
namespace
{
  GetEnumtorSet::~ GetEnumtorSet ()
         {}
}
namespace gram
{
  void getEnumtorSet (basl::Nonterm & nonterm, smtc::EnumtorPtrVector & enumtor_set)
  {
    nonterm.accept (GetEnumtorSet (enumtor_set));
  }
}
#undef LZZ_INLINE
