// smtc_IsNameBitf.cpp
//

#include "smtc_IsNameBitf.h"
// semantic
#include "smtc_Name.h"
#include "smtc_NameVisitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct IsNameBitf : NameVisitor
  {
    bool & result;
    void visit (BitfName const & name) const;
  public:
    explicit IsNameBitf (bool & result);
    ~ IsNameBitf ();
  };
}
namespace
{
  void IsNameBitf::visit (BitfName const & name) const
    {
      result = true;
    }
}
namespace
{
  LZZ_INLINE IsNameBitf::IsNameBitf (bool & result)
    : result (result)
         {}
}
namespace
{
  IsNameBitf::~ IsNameBitf ()
         {}
}
namespace smtc
{
  bool isNameBitf (NamePtr const & name)
  {
    bool result = false;
    name->accept (IsNameBitf (result));
    return result;
  }
}
#undef LZZ_INLINE
