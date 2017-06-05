// smtc_TmplParam.h
//

#ifndef LZZ_smtc_TmplParam_h
#define LZZ_smtc_TmplParam_h
// semantic
#include "smtc_Param.h"
#include "smtc_ParamPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplParam : public Param
  {
    ParamPtrVector m_param_set;
    NamePtr m_def_name;
  public:
    TmplParam (NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & def_name);
    ~ TmplParam ();
    ParamPtrVector const & getParamSet () const;
    bool hasDefaultName () const;
    NamePtr const & getDefaultName () const;
    util::String toString (bool is_decl) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplParam.inl"
#endif
#endif
