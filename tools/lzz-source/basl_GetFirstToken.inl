// basl_GetFirstToken.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE util::Loc getFirstLoc (Nonterm const & nonterm)
  {
    return getFirstToken (nonterm).getLoc ();
  }
}
#undef LZZ_INLINE
