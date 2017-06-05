// smtc_BaseSpec.h
//

#ifndef LZZ_smtc_BaseSpec_h
#define LZZ_smtc_BaseSpec_h
// semantic
#include "smtc_Access.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class BaseSpec
  {
    Access m_access;
    bool m_is_virtual;
    NamePtr m_base_name;
  public:
    BaseSpec (Access access, bool is_virtual, NamePtr const & base_name);
    virtual ~ BaseSpec ();
    Access getAccess () const;
    bool isVirtual () const;
    NamePtr const & getBaseName () const;
    virtual bool isLazy () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_BaseSpec.inl"
#endif
#endif
