// smtc_BaseNameVisitor.h
//

#ifndef LZZ_smtc_BaseNameVisitor_h
#define LZZ_smtc_BaseNameVisitor_h
#define LZZ_INLINE inline
namespace smtc
{
  class IdentBaseName;
}
namespace smtc
{
  class OperBaseName;
}
namespace smtc
{
  class DtorBaseName;
}
namespace smtc
{
  class ConvBaseName;
}
namespace smtc
{
  struct BaseNameVisitor
  {
    virtual void visit (IdentBaseName const & base_name) const;
    virtual void visit (OperBaseName const & base_name) const;
    virtual void visit (DtorBaseName const & base_name) const;
    virtual void visit (ConvBaseName const & base_name) const;
  public:
    explicit BaseNameVisitor ();
    ~ BaseNameVisitor ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_BaseNameVisitor.inl"
#endif
#endif
