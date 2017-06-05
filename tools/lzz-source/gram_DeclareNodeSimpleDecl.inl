// gram_DeclareNodeSimpleDecl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE void declareNodeSimpleDecl (basl::Nonterm & nonterm, smtc::ScopePtr const & cs)
  {
    SpecSel decl_spec_sel, dcl_spec_sel;
    smtc::CvType cv_type;
    return declareNodeSimpleDecl (nonterm, cs, decl_spec_sel, dcl_spec_sel, cv_type);
  }
}
#undef LZZ_INLINE
