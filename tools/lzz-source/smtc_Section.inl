// smtc_Section.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE std::ostream & Section::getStream ()
    {
      return m_os;
    }
}
#undef LZZ_INLINE
