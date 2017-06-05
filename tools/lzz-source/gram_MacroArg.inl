// gram_MacroArg.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE basl::TokenVector const & MacroArg::getTokenSet () const
    {
      return m_token_set;
    }
}
#undef LZZ_INLINE
