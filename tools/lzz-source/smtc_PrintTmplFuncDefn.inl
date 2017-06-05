// smtc_PrintTmplFuncDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE PrintTmplFuncDefn::PrintTmplFuncDefn (NamePtr const & qual_name)
    : PrintFuncDefn (qual_name)
    {}
}
#undef LZZ_INLINE
