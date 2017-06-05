// smtc_CreateIdentBaseName.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE BaseNamePtr createIdentBaseName (util::Loc const & loc, util::Ident const & ident)
  {
    return createIdentBaseName (loc, util::Ident (), ident);
  }
}
#undef LZZ_INLINE
