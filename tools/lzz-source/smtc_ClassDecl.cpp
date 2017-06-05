// smtc_ClassDecl.cpp
//

#include "smtc_ClassDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ClassDecl.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  ClassDecl::ClassDecl (ClassKey key, NamePtr const & name, bool is_dll_api)
    : m_key (key), m_name (name), m_is_dll_api (is_dll_api)
    {}
}
namespace smtc
{
  ClassDecl::~ ClassDecl ()
    {}
}
namespace smtc
{
  bool ClassDecl::isDllApi () const
    {
      return m_is_dll_api;
    }
}
#undef LZZ_INLINE
