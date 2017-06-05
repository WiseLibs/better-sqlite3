// smtc_Ns.cpp
//

#include "smtc_Ns.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_Ns.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  Ns::Ns ()
    {}
}
namespace smtc
{
  Ns::~ Ns ()
    {}
}
namespace smtc
{
  void Ns::addEntity (EntityPtr const & entity)
    {
      m_entity_set.push_back (entity);
    }
}
#undef LZZ_INLINE
