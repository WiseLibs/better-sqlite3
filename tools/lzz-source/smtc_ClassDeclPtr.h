// smtc_ClassDeclPtr.h
//

#ifndef LZZ_smtc_ClassDeclPtr_h
#define LZZ_smtc_ClassDeclPtr_h
#include "util_BPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassDecl;
}
namespace smtc
{
  typedef util::BPtr <ClassDecl> ClassDeclPtr;
}
#undef LZZ_INLINE
#endif
