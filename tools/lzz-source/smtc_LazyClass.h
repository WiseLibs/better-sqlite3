// smtc_LazyClass.h
//

#ifndef LZZ_smtc_LazyClass_h
#define LZZ_smtc_LazyClass_h
#include "smtc_ClassDefn.h"
#include "smtc_MbrInitPtrVector.h"
#include "smtc_ParamPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class LazyClass : public ClassDefn
  {
    int m_flags;
    ParamPtrVector m_param_set;
    bool m_vararg;
    MbrInitPtrVector m_mbr_init_set;
    bool m_vdtor;
  public:
    LazyClass (int flags, ClassKey key, NamePtr const & name, bool is_dll_api, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set);
    void addParam (ParamPtr const & param);
    ParamPtrVector const & getParamSet () const;
    bool hasVarArg () const;
    MbrInitPtrVector const & getMbrInitSet () const;
    void addMbrInit (MbrInitPtr const & mbr_init);
    void setVirtualDtor ();
    bool hasVirtualDtor () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_LazyClass.inl"
#endif
#endif
