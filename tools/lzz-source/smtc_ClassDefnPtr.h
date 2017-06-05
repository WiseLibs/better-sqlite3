// smtc_ClassDefnPtr.h
//

#ifndef LZZ_smtc_ClassDefnPtr_h
#define LZZ_smtc_ClassDefnPtr_h
// util
#include "util_DPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassDecl;
}
namespace smtc
{
  class ClassDefn;
}
namespace smtc
{
  typedef util::DPtr <ClassDefn, ClassDecl> ClassDefnPtr;
}
#undef LZZ_INLINE
#endif
