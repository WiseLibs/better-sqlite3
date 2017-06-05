// gram_Macro.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE Macro::~ Macro ()
    {}
}
namespace gram
{
  LZZ_INLINE util::Loc const & Macro::getLoc () const
    {
      return m_loc;
    }
}
namespace gram
{
  LZZ_INLINE util::Ident const & Macro::getName () const
    {
      return m_name;
    }
}
#undef LZZ_INLINE
