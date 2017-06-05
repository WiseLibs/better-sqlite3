// smtc_PrintTmplSpec.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE void PrintTmplSpec::operator () (TmplSpecPtr const & tmpl_spec) const
  {
    printTmplSpec (file, skind, tmpl_spec, is_decl);
  }
}
namespace smtc
{
  LZZ_INLINE PrintTmplSpec::PrintTmplSpec (FilePtr const & file, SectionKind skind, bool is_decl)
    : file (file), skind (skind), is_decl (is_decl)
              {}
}
#undef LZZ_INLINE
