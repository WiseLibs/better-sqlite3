// gram_GetElabType.h
//

#ifndef LZZ_gram_GetElabType_h
#define LZZ_gram_GetElabType_h
// semantic
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"

// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace gram
{
  void getElabType (basl::Nonterm & nonterm, smtc::ClassKey & key, smtc::NamePtr & name);
}
namespace gram
{
  void getElabType (basl::Nonterm & nonterm, smtc::ClassKey & key, smtc::NamePtr & name, bool & is_dll_api);
}
#undef LZZ_INLINE
#endif
