// smtc_VdfScope.h
//

#ifndef LZZ_smtc_VdfScope_h
#define LZZ_smtc_VdfScope_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ThrowSpecPtr.h"
#include "smtc_Scope.h"
#define LZZ_INLINE inline
namespace smtc
{
  class VdfScope : public Scope
  {
    NsPtr m_outer_ns;
    NamePtr m_base_type_name;
    CvType m_ret_type;
    NamePtr m_name;
    ParamPtrVector m_param_set;
    bool m_vararg;
    ThrowSpecPtr m_throw_spec;
    NsPtr m_private_ns;
  public:
    VdfScope (NsPtr const & outer_ns, NamePtr const & base_type_name, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, ThrowSpecPtr const & throw_spec, NsPtr const & private_ns);
    ~ VdfScope ();
    void accept (ScopeVisitor const & visitor) const;
    NsPtr const & getOuterNs () const;
    NamePtr const & getBaseTypeName () const;
    CvType const & getReturnType () const;
    NamePtr const & getName () const;
    ParamPtrVector const & getParamSet () const;
    bool hasVarArg () const;
    ThrowSpecPtr const & getThrowSpec () const;
    NsPtr const & getPrivateNs () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_VdfScope.inl"
#endif
#endif
