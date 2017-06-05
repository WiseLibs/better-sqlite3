// smtc_BuiltInType.tpl
//

#include "smtc_BuiltInType.h"
#include "util_AppendWithSpace.h"
namespace smtc
{
  template <typename T>
  BuiltInType <T>::BuiltInType ()
    {}
}
namespace smtc
{
  template <typename T>
  BuiltInType <T>::~ BuiltInType ()
    {}
}
namespace smtc
{
  template <typename T>
  TypeKind BuiltInType <T>::getKind () const
    {
      return T::KIND;
    }
}
namespace smtc
{
  template <typename T>
  util::String BuiltInType <T>::toString (util::String const & dcl, bool c, bool v) const
    {
      util::String str = T::NAME;
      appendCv (str, c, v);
      util::appendWithSpace (str, dcl);
      return str;
    }
}
