// smtc_GetBuiltInType.h
//

#ifndef LZZ_smtc_GetBuiltInType_h
#define LZZ_smtc_GetBuiltInType_h
// semantic
#include "smtc_TypePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypePtr getBoolType ();
}
namespace smtc
{
  TypePtr getCharType ();
}
namespace smtc
{
  TypePtr getSignedCharType ();
}
namespace smtc
{
  TypePtr getUnsignedCharType ();
}
namespace smtc
{
  TypePtr getWideCharType ();
}
namespace smtc
{
  TypePtr getShortIntType ();
}
namespace smtc
{
  TypePtr getUnsignedShortIntType ();
}
namespace smtc
{
  TypePtr getIntType ();
}
namespace smtc
{
  TypePtr getUnsignedIntType ();
}
namespace smtc
{
  TypePtr getLongIntType ();
}
namespace smtc
{
  TypePtr getUnsignedLongIntType ();
}
namespace smtc
{
  TypePtr getLongLongIntType ();
}
namespace smtc
{
  TypePtr getUnsignedLongLongIntType ();
}
namespace smtc
{
  TypePtr getFloatType ();
}
namespace smtc
{
  TypePtr getDoubleType ();
}
namespace smtc
{
  TypePtr getLongDoubleType ();
}
namespace smtc
{
  TypePtr getVoidType ();
}
#undef LZZ_INLINE
#endif
