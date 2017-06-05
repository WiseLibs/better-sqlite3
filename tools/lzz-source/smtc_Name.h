// smtc_Name.h
//

#ifndef LZZ_smtc_Name_h
#define LZZ_smtc_Name_h
#define LZZ_INLINE inline
namespace smtc
{
  class NameVisitor;
}
namespace smtc
{
  class Name
  {
  public:
    Name ();
    virtual ~ Name ();
    virtual void accept (NameVisitor const & visitor) const = 0;
  };
}
#undef LZZ_INLINE
#endif
