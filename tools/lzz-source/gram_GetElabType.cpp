// gram_GetElabType.cpp
//

#include "gram_GetElabType.h"
// gram
#include "gram_GetClassKey.h"
#include "gram_GetNodeName.h"
#include "gram_Nonterm.h"
#include "gram_Visitor.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct GetElabType : Visitor
  {
    smtc::ClassKey & key;
    smtc::NamePtr & name;
    bool & is_dll_api;
    void visit (ElabTypeNode & node) const;
  public:
    explicit GetElabType (smtc::ClassKey & key, smtc::NamePtr & name, bool & is_dll_api);
    ~ GetElabType ();
  };
}
namespace
{
  void GetElabType::visit (ElabTypeNode & node) const
    {
      key = getClassKey (node.getClassKey ().getNumber ());
      name = getNodeName (node.getObjName ());
      is_dll_api = node.getDllApiOpt ().isSet ();
    }
}
namespace
{
  LZZ_INLINE GetElabType::GetElabType (smtc::ClassKey & key, smtc::NamePtr & name, bool & is_dll_api)
    : key (key), name (name), is_dll_api (is_dll_api)
         {}
}
namespace
{
  GetElabType::~ GetElabType ()
         {}
}
namespace gram
{
  void getElabType (basl::Nonterm & nonterm, smtc::ClassKey & key, smtc::NamePtr & name)
  {
    bool is_dll_api = false;
    getElabType (nonterm, key, name, is_dll_api);
  }
}
namespace gram
{
  void getElabType (basl::Nonterm & nonterm, smtc::ClassKey & key, smtc::NamePtr & name, bool & is_dll_api)
  {
    nonterm.accept (GetElabType (key, name, is_dll_api));
  }
}
#undef LZZ_INLINE
