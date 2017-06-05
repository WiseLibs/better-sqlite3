// smtc_Enumtor.cpp
//

#include "smtc_Enumtor.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_Enumtor.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  Enumtor::Enumtor (NamePtr const & name, gram::Block const & init)
    : m_name (name), m_init (init)
    {}
}
namespace smtc
{
  Enumtor::~ Enumtor ()
    {}
}
#undef LZZ_INLINE
