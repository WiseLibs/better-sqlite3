// smtc_BaseNameToString.cpp
//

#include "smtc_BaseNameToString.h"
// semantic
#include "smtc_BaseNameVisitor.h"
#include "smtc_ConvBaseName.h"
#include "smtc_DtorBaseName.h"
#include "smtc_IdentBaseName.h"
#include "smtc_OperBaseName.h"
#include "smtc_OperToString.h"

// util
#include "util_AppendWithSpace.h"
#include "util_IdentToString.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  using namespace util;
}
namespace
{
  struct BaseNameToString : BaseNameVisitor
  {
    util::String & str;
    void visit (IdentBaseName const & base_name) const;
    void visit (OperBaseName const & base_name) const;
    void visit (DtorBaseName const & base_name) const;
    void visit (ConvBaseName const & base_name) const;
    void addMacro (BaseName const & base_name) const;
  public:
    explicit BaseNameToString (util::String & str);
    ~ BaseNameToString ();
  };
}
namespace
{
  void BaseNameToString::visit (IdentBaseName const & base_name) const
    {
      addMacro (base_name);
      appendWithSpace (str, identToString (base_name.getIdent ()));
    }
}
namespace
{
  void BaseNameToString::visit (OperBaseName const & base_name) const
    {
      addMacro (base_name);
      appendWithSpace (str, "operator");
      appendWithSpace (str, operToString (base_name.getOperKind ()));
    }
}
namespace
{
  void BaseNameToString::visit (DtorBaseName const & base_name) const
    {
      addMacro (base_name);
      appendWithSpace (str, '~');
      appendWithSpace (str, identToString (base_name.getIdent ()));
    }
}
namespace
{
  void BaseNameToString::visit (ConvBaseName const & base_name) const
    {
      addMacro (base_name);
      appendWithSpace (str, "operator");
      appendWithSpace (str, base_name.getCvType ().toString ());
    }
}
namespace
{
  void BaseNameToString::addMacro (BaseName const & base_name) const
    {
      if (base_name.hasMacro ())
      {
        str = base_name.getMacro ().c_str ();
      }
    }
}
namespace
{
  LZZ_INLINE BaseNameToString::BaseNameToString (util::String & str)
    : str (str)
         {}
}
namespace
{
  BaseNameToString::~ BaseNameToString ()
         {}
}
namespace smtc
{
  util::String baseNameToString (BaseNamePtr const & base_name)
  {
    util::String str;
    base_name->accept (BaseNameToString (str));
    return str;
  }
}
#undef LZZ_INLINE
