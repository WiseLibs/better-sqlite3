// smtc_ParamToNavCtorParam.h
//

#ifndef LZZ_smtc_ParamToNavCtorParam_h
#define LZZ_smtc_ParamToNavCtorParam_h
// semantic
#include "smtc_ParamPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr paramToNavCtorParam (ParamPtr const & param);
}
namespace smtc
{
  struct ParamToNavCtorParam
  {
    ParamPtr operator () (ParamPtr const & param) const;
  public:
    explicit ParamToNavCtorParam ();
    ~ ParamToNavCtorParam ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ParamToNavCtorParam.inl"
#endif
#endif
