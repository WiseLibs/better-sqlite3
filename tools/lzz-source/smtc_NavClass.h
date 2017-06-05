// smtc_NavClass.h
//

#ifndef LZZ_smtc_NavClass_h
#define LZZ_smtc_NavClass_h
// semantic
#include "smtc_CvType.h"
#include "smtc_LazyClass.h"
#include "smtc_ObjPtrVector.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NavClass : public LazyClass
  {
    CvType m_ret_type;
    CvType m_node_type;
    ParamPtrVector m_submit_param_set;
    ObjPtrVector m_submit_obj_set;
    gram::Block m_return_stmt;
  public:
    NavClass (int flags, NamePtr const & name, ParamPtrVector const & ctor_param_set, BaseSpecPtrVector const & base_spec_set, CvType const & ret_type, CvType const & node_type, ParamPtrVector const & submit_param_set);
    CvType const & getReturnType () const;
    ParamPtrVector const & getSubmitParamSet () const;
    CvType const & getNodeType () const;
    void addSubmitObj (ObjPtr const & obj);
    ObjPtrVector const & getSubmitObjSet () const;
    bool hasReturnStmt () const;
    void setReturnStmt (gram::Block const & stmt);
    gram::Block const & getReturnStmt () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NavClass.inl"
#endif
#endif
