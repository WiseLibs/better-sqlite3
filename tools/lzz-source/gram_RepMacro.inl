// gram_RepMacro.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE RepMacro::~ RepMacro ()
    {}
}
namespace gram
{
  LZZ_INLINE basl::TokenVector const & RepMacro::getRepSet () const
    {
      return m_rep_set;
    }
}
#undef LZZ_INLINE
