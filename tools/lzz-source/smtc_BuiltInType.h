// smtc_BuiltInType.h
//

#ifndef LZZ_smtc_BuiltInType_h
#define LZZ_smtc_BuiltInType_h
// semantic
#include "smtc_BuiltIn.h"
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  template <typename T>
  class BuiltInType : public Type
  {
  public:
    BuiltInType ();
    ~ BuiltInType ();
    TypeKind getKind () const;
    util::String toString (util::String const & dcl, bool c, bool v) const;
  };
}
namespace smtc
{
  typedef BuiltInType <Bool> BoolType;
}
namespace smtc
{
  typedef BuiltInType <Char> CharType;
}
namespace smtc
{
  typedef BuiltInType <SignedChar> SignedCharType;
}
namespace smtc
{
  typedef BuiltInType <UnsignedChar> UnsignedCharType;
}
namespace smtc
{
  typedef BuiltInType <WideChar> WideCharType;
}
namespace smtc
{
  typedef BuiltInType <ShortInt> ShortIntType;
}
namespace smtc
{
  typedef BuiltInType <UnsignedShortInt> UnsignedShortIntType;
}
namespace smtc
{
  typedef BuiltInType <Int> IntType;
}
namespace smtc
{
  typedef BuiltInType <UnsignedInt> UnsignedIntType;
}
namespace smtc
{
  typedef BuiltInType <LongInt> LongIntType;
}
namespace smtc
{
  typedef BuiltInType <UnsignedLongInt> UnsignedLongIntType;
}
namespace smtc
{
  typedef BuiltInType <LongLongInt> LongLongIntType;
}
namespace smtc
{
  typedef BuiltInType <UnsignedLongLongInt> UnsignedLongLongIntType;
}
namespace smtc
{
  typedef BuiltInType <Float> FloatType;
}
namespace smtc
{
  typedef BuiltInType <Double> DoubleType;
}
namespace smtc
{
  typedef BuiltInType <LongDouble> LongDoubleType;
}
namespace smtc
{
  typedef BuiltInType <Void> VoidType;
}
#undef LZZ_INLINE
#endif
