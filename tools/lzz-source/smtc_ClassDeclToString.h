// smtc_ClassDeclToString.h
//

#ifndef LZZ_smtc_ClassDeclToString_h
#define LZZ_smtc_ClassDeclToString_h
// semantic
#include "smtc_ClassDeclPtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  util::String classDeclToString (ClassDeclPtr const & class_decl);
}
#undef LZZ_INLINE
#endif
