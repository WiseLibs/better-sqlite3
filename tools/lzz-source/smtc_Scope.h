// smtc_Scope.h
//

#ifndef LZZ_smtc_Scope_h
#define LZZ_smtc_Scope_h
#define LZZ_INLINE inline
namespace smtc
{
  class ScopeVisitor;
}
namespace smtc
{
  class Scope
  {
  public:
    Scope ();
    virtual ~ Scope ();
    virtual void accept (ScopeVisitor const & visitor) const = 0;
  };
}
#undef LZZ_INLINE
#endif
