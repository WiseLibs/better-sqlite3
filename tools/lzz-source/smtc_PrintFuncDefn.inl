// smtc_PrintFuncDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE PrintFuncDefn::PrintFuncDefn (NamePtr const & qual_name)
    : PrintFuncDecl (qual_name)
    {}
}
#undef LZZ_INLINE
