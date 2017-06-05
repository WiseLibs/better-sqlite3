// smtc_IsNameQual.cpp
//

#include "smtc_IsNameQual.h"
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
  struct IsNameQual : NameVisitor
  {
    bool & result;
    void visit (QualName const & name) const;
  public:
    explicit IsNameQual (bool & result);
    ~ IsNameQual ();
  };
}
namespace
{
  void IsNameQual::visit (QualName const & name) const
    {
      result = true;
    }
}
namespace
{
  LZZ_INLINE IsNameQual::IsNameQual (bool & result)
    : result (result)
         {}
}
namespace
{
  IsNameQual::~ IsNameQual ()
         {}
}
namespace smtc
{
  bool isNameQual (NamePtr const & name)
  {
    bool result = false;
    name->accept (IsNameQual (result));
    return result;
  }
}
#undef LZZ_INLINE
