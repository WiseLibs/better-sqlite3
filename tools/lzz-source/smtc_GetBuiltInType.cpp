// smtc_GetBuiltInType.cpp
//

#include "smtc_GetBuiltInType.h"
// semantic
#include "smtc_BuiltInType.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  template <typename T>
  TypePtr getBuiltInType ();
}
namespace
{
  template <typename T>
  TypePtr getBuiltInType ()
  {
    static BuiltInType <T> type;
    return TypePtr::unref (& type);
  }
}
namespace smtc
{
  TypePtr getBoolType ()
  {
    return getBuiltInType <Bool> ();
  }
}
namespace smtc
{
  TypePtr getCharType ()
  {
    return getBuiltInType <Char> ();
  }
}
namespace smtc
{
  TypePtr getSignedCharType ()
  {
    return getBuiltInType <SignedChar> ();
  }
}
namespace smtc
{
  TypePtr getUnsignedCharType ()
  {
    return getBuiltInType <UnsignedChar> ();
  }
}
namespace smtc
{
  TypePtr getWideCharType ()
  {
    return getBuiltInType <WideChar> ();
  }
}
namespace smtc
{
  TypePtr getShortIntType ()
  {
    return getBuiltInType <ShortInt> ();
  }
}
namespace smtc
{
  TypePtr getUnsignedShortIntType ()
  {
    return getBuiltInType <UnsignedShortInt> ();
  }
}
namespace smtc
{
  TypePtr getIntType ()
  {
    return getBuiltInType <Int> ();
  }
}
namespace smtc
{
  TypePtr getUnsignedIntType ()
  {
    return getBuiltInType <UnsignedInt> ();
  }
}
namespace smtc
{
  TypePtr getLongIntType ()
  {
    return getBuiltInType <LongInt> ();
  }
}
namespace smtc
{
  TypePtr getUnsignedLongIntType ()
  {
    return getBuiltInType <UnsignedLongInt> ();
  }
}
namespace smtc
{
  TypePtr getLongLongIntType ()
  {
    return getBuiltInType <LongLongInt> ();
  }
}
namespace smtc
{
  TypePtr getUnsignedLongLongIntType ()
  {
    return getBuiltInType <UnsignedLongLongInt> ();
  }
}
namespace smtc
{
  TypePtr getFloatType ()
  {
    return getBuiltInType <Float> ();
  }
}
namespace smtc
{
  TypePtr getDoubleType ()
  {
    return getBuiltInType <Double> ();
  }
}
namespace smtc
{
  TypePtr getLongDoubleType ()
  {
    return getBuiltInType <LongDouble> ();
  }
}
namespace smtc
{
  TypePtr getVoidType ()
  {
    return getBuiltInType <Void> ();
  }
}
#undef LZZ_INLINE
