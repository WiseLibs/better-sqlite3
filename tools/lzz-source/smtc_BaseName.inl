// smtc_BaseName.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::Loc const & BaseName::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE bool BaseName::hasMacro () const
    {
      return m_macro.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE util::Ident const & BaseName::getMacro () const
    {
      return m_macro;
    }
}
#undef LZZ_INLINE
