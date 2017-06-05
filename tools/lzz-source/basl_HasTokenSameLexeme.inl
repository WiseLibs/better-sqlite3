// basl_HasTokenSameLexeme.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE bool HasTokenSameLexeme::operator () (Token const & a, Token const & b) const
  {
    return a.getLexeme () == b.getLexeme ();
  }
}
namespace basl
{
  LZZ_INLINE HasTokenSameLexeme::HasTokenSameLexeme ()
              {}
}
#undef LZZ_INLINE
