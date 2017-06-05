// gram_GetBaseSpecSet.cpp
//

#include "gram_GetBaseSpecSet.h"
// gram
#include "gram_GetAccess.h"
#include "gram_GetNodeBlockSet.h"
#include "gram_GetNodeName.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_GetBaseSpec.h"
#include "smtc_GetLazyBaseSpec.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetBaseSpecSet : Visitor
  {
    smtc::BaseSpecPtrVector & base_spec_set;
    void visit (BaseSpec1Node & node) const;
    void visit (LazyBaseSpec1Node & node) const;
    void visit (BaseSpec2Node & node) const;
    void visit (LazyBaseSpec2Node & node) const;
    void visit (BaseSpec3Node & node) const;
    void visit (LazyBaseSpec3Node & node) const;
  public:
    explicit GetBaseSpecSet (smtc::BaseSpecPtrVector & base_spec_set);
    ~ GetBaseSpecSet ();
  };
}
namespace
{
  void GetBaseSpecSet::visit (BaseSpec1Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      base_spec_set.push_back (smtc::getBaseSpec (smtc::DEFAULT_ACCESS, false, name));
    }
}
namespace
{
  void GetBaseSpecSet::visit (LazyBaseSpec1Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      gram::BlockVector arg_set;
      getNodeBlockSet (node.getBaseInit (), arg_set);
      base_spec_set.push_back (smtc::getLazyBaseSpec (smtc::DEFAULT_ACCESS, false, name, arg_set));
    }
}
namespace
{
  void GetBaseSpecSet::visit (BaseSpec2Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::Access access = smtc::DEFAULT_ACCESS;
      basl::Token & access_node = node.getAccessOpt ();
      if (access_node.isSet ())
      {
        access = getAccess (access_node.getNumber ());
      }
      base_spec_set.push_back (smtc::getBaseSpec (access, true, name));
    }
}
namespace
{
  void GetBaseSpecSet::visit (LazyBaseSpec2Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::Access access = smtc::DEFAULT_ACCESS;
      basl::Token & access_node = node.getAccessOpt ();
      if (access_node.isSet ())
      {
        access = getAccess (access_node.getNumber ());
      }
      gram::BlockVector arg_set;
      getNodeBlockSet (node.getBaseInit (), arg_set);
      base_spec_set.push_back (smtc::getLazyBaseSpec (access, true, name, arg_set));
    }
}
namespace
{
  void GetBaseSpecSet::visit (BaseSpec3Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::Access access = getAccess (node.getAccess ().getNumber ());
      base_spec_set.push_back (smtc::getBaseSpec (access, node.getVirtualOpt ().isSet (), name));
    }
}
namespace
{
  void GetBaseSpecSet::visit (LazyBaseSpec3Node & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      smtc::Access access = getAccess (node.getAccess ().getNumber ());
      gram::BlockVector arg_set;
      getNodeBlockSet (node.getBaseInit (), arg_set);
      base_spec_set.push_back (smtc::getLazyBaseSpec (access, node.getVirtualOpt ().isSet (), name, arg_set));
    }
}
namespace
{
  LZZ_INLINE GetBaseSpecSet::GetBaseSpecSet (smtc::BaseSpecPtrVector & base_spec_set)
    : base_spec_set (base_spec_set)
         {}
}
namespace
{
  GetBaseSpecSet::~ GetBaseSpecSet ()
         {}
}
namespace gram
{
  void getBaseSpecSet (basl::Nonterm & nonterm, smtc::BaseSpecPtrVector & base_spec_set)
  {
    nonterm.accept (GetBaseSpecSet (base_spec_set));
  }
}
#undef LZZ_INLINE
