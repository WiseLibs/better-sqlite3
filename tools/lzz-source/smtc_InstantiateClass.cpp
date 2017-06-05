// smtc_InstantiateClass.cpp
//

#include "smtc_InstantiateClass.h"
#include "smtc_CreateClassDecl.h"
#include "smtc_CreateClassInstEntity.h"
#include "smtc_Message.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_TmplInstScope.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct InstantiateClass : ScopeVisitor
  {
    ClassKey key;
    NamePtr const & name;
    bool is_dll_api;
    void visit (NsScope const & scope) const;
  public:
    explicit InstantiateClass (ClassKey key, NamePtr const & name, bool is_dll_api);
    ~ InstantiateClass ();
  };
}
namespace smtc
{
  void instantiateClass (ScopePtr const & scope, ClassKey key, NamePtr const & name, bool is_dll_api)
  {
    scope->accept (InstantiateClass (key, name, is_dll_api));
  }
}
namespace
{
  void InstantiateClass::visit (NsScope const & scope) const
    {
      // create class decl and add to namespace
      ClassDeclPtr class_decl = createClassDecl (key, name, is_dll_api);
      scope.getNs ()->addEntity (createClassInstEntity (class_decl));
    }
}
namespace
{
  LZZ_INLINE InstantiateClass::InstantiateClass (ClassKey key, NamePtr const & name, bool is_dll_api)
    : key (key), name (name), is_dll_api (is_dll_api)
         {}
}
namespace
{
  InstantiateClass::~ InstantiateClass ()
         {}
}
#undef LZZ_INLINE
