// smtc_CreateEnumtor.cpp
//

#include "smtc_CreateEnumtor.h"
// semantic
#include "smtc_Enumtor.h"
#define LZZ_INLINE inline
namespace smtc
{
  EnumtorPtr createEnumtor (NamePtr const & name, gram::Block const & init)
  {
    return new Enumtor (name, init);
  }
}
#undef LZZ_INLINE
