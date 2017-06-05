// smtc_CreateEnumtor.h
//

#ifndef LZZ_smtc_CreateEnumtor_h
#define LZZ_smtc_CreateEnumtor_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_EnumtorPtr.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  EnumtorPtr createEnumtor (NamePtr const & name, gram::Block const & init = gram::Block ());
}
#undef LZZ_INLINE
#endif
