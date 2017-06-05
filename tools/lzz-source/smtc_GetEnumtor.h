// smtc_GetEnumtor.h
//

#ifndef LZZ_smtc_GetEnumtor_h
#define LZZ_smtc_GetEnumtor_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_EnumtorPtr.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  EnumtorPtr getEnumtor (NamePtr const & name, gram::Block const & init);
}
namespace smtc
{
  EnumtorPtr getEnumtor (NamePtr const & name);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_GetEnumtor.inl"
#endif
#endif
