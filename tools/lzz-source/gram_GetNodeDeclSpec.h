// gram_GetNodeDeclSpec.h
//

#ifndef LZZ_gram_GetNodeDeclSpec_h
#define LZZ_gram_GetNodeDeclSpec_h
// gram
#include "gram_SpecSel.h"

// basil
#include "basl_Nonterm.h"

// semantic
#include "smtc_Cv.h"
#include "smtc_CvType.h"
#define LZZ_INLINE inline
namespace gram
{
  void getNodeDeclSpec (basl::Nonterm & nonterm, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type);
}
namespace gram
{
  void getNodeDeclSpec (basl::Nonterm & nonterm, smtc::CvType & cv_type);
}
namespace gram
{
  void getNodeLazyCtorSpec (basl::Nonterm & nonterm, SpecSel & dcl_spec_sel, smtc::Cv & cv);
}
#undef LZZ_INLINE
#endif
