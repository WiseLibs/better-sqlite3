// smtc_GetEnumtor.cpp
//

#include "smtc_GetEnumtor.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_GetEnumtor.inl"
#endif
// semantic
#include "smtc_CreateEnumtor.h"
#define LZZ_INLINE inline
namespace smtc
{
  EnumtorPtr getEnumtor (NamePtr const & name, gram::Block const & init)
  {
    // TBD: check name
    // ...

    // trim init
    if (init.isSet ())
    {
      init.trim ();
    }
    
    return createEnumtor (name, init);
  }
}
#undef LZZ_INLINE
