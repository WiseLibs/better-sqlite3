// smtc_CreateConvBaseName.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE BaseNamePtr createConvBaseName (util::Loc const & loc, CvType const & cv_type)
  {
    return createConvBaseName (loc, util::Ident (), cv_type);
  }
}
#undef LZZ_INLINE
