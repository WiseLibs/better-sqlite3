// smtc_PrintTmplFuncDecl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE PrintTmplFuncDecl::PrintTmplFuncDecl (NamePtr const & qual_name)
    : PrintFuncDecl (qual_name)
    {}
}
namespace smtc
{
  LZZ_INLINE void PrintTmplFuncDecl::print (FilePtr const & file, SectionKind skind, TmplFuncDeclPtr const & tmpl_func_decl, NsPtr const & ns)
    {
      print (file, skind, tmpl_func_decl, TmplSpecPtrVector (), ns);
    }
}
namespace smtc
{
  LZZ_INLINE void PrintTmplFuncDecl::print (FilePtr const & file, SectionKind skind, TmplFuncDeclPtr const & tmpl_func_decl)
    {
      print (file, skind, tmpl_func_decl, TmplSpecPtrVector ());
    }
}
#undef LZZ_INLINE
