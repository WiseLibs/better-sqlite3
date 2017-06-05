// gram_GetNodeDcl.h
//

#ifndef LZZ_gram_GetNodeDcl_h
#define LZZ_gram_GetNodeDcl_h
// gram
#include "gram_SpecSel.h"

// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"
#include "smtc_ThrowSpecPtr.h"
#define LZZ_INLINE inline
namespace gram
{
  void getNodeAbstractDcl (basl::Nonterm & nonterm, smtc::CvType & dcl_cv_type);
}
namespace gram
{
  void getNodeParamDcl (basl::Nonterm & nonterm, SpecSel & dcl_spec_sel, smtc::CvType & dcl_cv_type, smtc::NamePtr & name);
}
namespace gram
{
  void getNodeObjDcl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name);
}
namespace gram
{
  void getNodeFuncDcl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::ParamPtrVector & param_set, bool & vararg, smtc::Cv & cv, smtc::ThrowSpecPtr & throw_spec);
}
namespace gram
{
  void getNodeFunctorDcl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type, smtc::CvType & dcl_cv_type, smtc::NamePtr & name, smtc::ParamPtrVector & ctor_param_set, bool & ctor_vararg, smtc::ParamPtrVector & call_param_set, bool & call_vararg, smtc::Cv & cv, smtc::ThrowSpecPtr & throw_spec);
}
namespace gram
{
  void getNodeNavDcl (basl::Nonterm & nonterm, SpecSel & dcl_spec_sel, smtc::CvType & ret_type, smtc::NamePtr & name, smtc::CvType & node_type, smtc::ParamPtrVector & param_set);
}
namespace gram
{
  void visitVdfDataParamList (basl::Nonterm & vdf_data_param_list, smtc::ParamPtrVector & param_set, bool & vararg);
}
#undef LZZ_INLINE
#endif
