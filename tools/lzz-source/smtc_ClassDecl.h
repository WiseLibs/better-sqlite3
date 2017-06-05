// smtc_ClassDecl.h
//

#ifndef LZZ_smtc_ClassDecl_h
#define LZZ_smtc_ClassDecl_h
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassDecl
  {
    ClassKey m_key;
    NamePtr m_name;
    bool m_is_dll_api;
  public:
    ClassDecl (ClassKey key, NamePtr const & name, bool is_dll_api);
    virtual ~ ClassDecl ();
    ClassKey getKey () const;
    NamePtr const & getName () const;
    bool isDllApi () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ClassDecl.inl"
#endif
#endif
