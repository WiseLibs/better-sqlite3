// smtc_NameVisitor.h
//

#ifndef LZZ_smtc_NameVisitor_h
#define LZZ_smtc_NameVisitor_h
#define LZZ_INLINE inline
namespace smtc
{
  class QualName;
}
namespace smtc
{
  class BitfName;
}
namespace smtc
{
  class TmplName;
}
namespace smtc
{
  class NonTmplName;
}
namespace smtc
{
  struct NameVisitor
  {
    virtual void visit (QualName const & name) const;
    virtual void visit (TmplName const & name) const;
    virtual void visit (NonTmplName const & name) const;
    virtual void visit (BitfName const & name) const;
  public:
    explicit NameVisitor ();
    ~ NameVisitor ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NameVisitor.inl"
#endif
#endif
