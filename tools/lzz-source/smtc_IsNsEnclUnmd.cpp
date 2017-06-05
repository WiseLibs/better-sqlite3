// smtc_IsNsEnclUnmd.cpp
//

#include "smtc_IsNsEnclUnmd.h"
// semantic
#include "smtc_NestedNs.h"
#include "smtc_NsVisitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct IsNsEnclUnmd : NsVisitor
  {
    bool & result;
    void visit (UnnamedNs const & ns) const;
    void visit (NestedNs const & ns) const;
  public:
    explicit IsNsEnclUnmd (bool & result);
    ~ IsNsEnclUnmd ();
  };
}
namespace
{
  void IsNsEnclUnmd::visit (UnnamedNs const & ns) const
    {
      result = true;
    }
}
namespace
{
  void IsNsEnclUnmd::visit (NestedNs const & ns) const
    {
      ns.getEnclNs ()->accept (* this);
    }
}
namespace
{
  LZZ_INLINE IsNsEnclUnmd::IsNsEnclUnmd (bool & result)
    : NsVisitor (), result (result)
         {}
}
namespace
{
  IsNsEnclUnmd::~ IsNsEnclUnmd ()
         {}
}
namespace smtc
{
  bool isNsEnclUnmd (NsPtr const & ns)
  {
    // return false;
    bool result = false;
    ns->accept (IsNsEnclUnmd (result));
    return result;
  }
}
#undef LZZ_INLINE
