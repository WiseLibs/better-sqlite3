// smtc_DeclareParamAsMbrObj.h
//

#ifndef LZZ_smtc_DeclareParamAsMbrObj_h
#define LZZ_smtc_DeclareParamAsMbrObj_h
// semantic
#include "smtc_LazyClassPtr.h"
#include "smtc_ParamPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareParamAsMbrObj (LazyClassPtr const & lazy_class, ParamPtr const & param, bool as_ref = false);
}
namespace smtc
{
  struct DeclareParamAsMbrObj
  {
    LazyClassPtr const & lazy_class;
    bool as_ref;
    void operator () (ParamPtr const & param) const;
  public:
    explicit DeclareParamAsMbrObj (LazyClassPtr const & lazy_class, bool as_ref = false);
    ~ DeclareParamAsMbrObj ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_DeclareParamAsMbrObj.inl"
#endif
#endif
