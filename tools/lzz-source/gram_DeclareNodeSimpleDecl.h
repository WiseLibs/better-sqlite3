// gram_DeclareNodeSimpleDecl.h
//

#ifndef LZZ_gram_DeclareNodeSimpleDecl_h
#define LZZ_gram_DeclareNodeSimpleDecl_h
// gram
#include "gram_SpecSel.h"

// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_CvType.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace gram
{
  void declareNodeSimpleDecl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type);
}
namespace gram
{
  void declareNodeSimpleDecl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_DeclareNodeSimpleDecl.inl"
#endif
#endif
