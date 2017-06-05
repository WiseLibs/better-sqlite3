// smtc_CreateDtorBaseName.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE BaseNamePtr createDtorBaseName (util::Loc const & loc, util::Ident const & ident)
  {
    return createDtorBaseName (loc, util::Ident (), ident);
  }
}
#undef LZZ_INLINE
