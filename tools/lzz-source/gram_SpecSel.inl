// gram_SpecSel.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE SpecSel::SpecSel ()
    : m_flags (0)
    {}
}
namespace gram
{
  LZZ_INLINE bool SpecSel::anySet () const
    {
      return m_flags != 0;
    }
}
namespace gram
{
  LZZ_INLINE int SpecSel::getFlags () const
    {
      return m_flags;
    }
}
#undef LZZ_INLINE
